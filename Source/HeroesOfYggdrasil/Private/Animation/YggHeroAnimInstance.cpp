
#include "Animation/YggHeroAnimInstance.h"

#include "Player/YggHero.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

#include "Attribute/HeroAttributeComponent.h"


UYggHeroAnimInstance::UYggHeroAnimInstance()
{
	MontageMap.Add(TEXT("Attack"), NewObject<UAnimMontage>());
	MontageMap.Add(TEXT("SkillQ"), NewObject<UAnimMontage>());
	MontageMap.Add(TEXT("SkillE"), NewObject<UAnimMontage>());
	MontageMap.Add(TEXT("SkillR"), NewObject<UAnimMontage>());
}

// 애니메이션 블루프린트가 초기화될 때 실행되는 함수
void UYggHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// 애니메이션의 소유자가 되는 캐릭터를 가져와서 Hero 변수에 저장
	Hero = Cast<AYggHero>(TryGetPawnOwner());
	if (Hero == nullptr)
	{
		return;
	}

	// 캐릭터의 이동 컴포넌트를 가져와 저장
	CharacterMovementComponent = Hero->GetCharacterMovement();
	HeroAttributeComponent = Hero->GetHeroAttributeComponent();
}

// 애니메이션이 업데이트될 때 실행되는 함수
void UYggHeroAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaTime);

	// 이동 컴포넌트가 없으면 업데이트하지 않음
	if (CharacterMovementComponent == nullptr)
	{
		return;
	}

	// 현재 이동 속도를 2D 벡터 크기로 계산 (XY 평면 속도)
	GroundSpeed = UKismetMathLibrary::VSizeXY(CharacterMovementComponent->Velocity);

	// 이동 방향을 계산하여 Direction 변수에 저장
	Direction = CalculateDirection(CharacterMovementComponent->Velocity, Hero->GetActorRotation());

	// 전체 속도 크기를 저장
	Speed = CharacterMovementComponent->Velocity.Size();

	// 캐릭터가 공중에 떠 있는지 확인하여 저장
	bIsInAir = CharacterMovementComponent->IsFalling();

	// 에임 오프셋 값 업데이트
	UpdateAimOffset();
}

// 지정된 몽타주를 재생하는 함수
void UYggHeroAnimInstance::PlayMontage(FName MontageName, float PlayRate)
{
	// MontageMap에 해당하는 키가 없으면 실행하지 않음
	if (MontageMap.Contains(MontageName) == false)
	{
		return;
	}
	if (MontageMap[MontageName] == nullptr)
	{
		return;
	}
	// 맵에서 몽타주를 찾아 실행
	if (Montage_IsPlaying(MontageMap[MontageName]))
	{
		return;
	}
	PlayMontageEvent(MontageMap[MontageName], PlayRate);
}

void UYggHeroAnimInstance::JumpMontage(FName MontageName, FName SectionName)
{
	if (MontageMap.Contains(MontageName) == false)
	{
		return;
	}
	Montage_JumpToSection(SectionName, MontageMap[MontageName]);
}

void UYggHeroAnimInstance::StopMontage()
{
	Montage_Stop(0.5f);
}

void UYggHeroAnimInstance::EndMontageEvent()
{
	Hero->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotRollable"));
	Hero->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotMoveable"));
	Hero->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotAttackable"));
}

// 에임 오프셋을 계산하는 함수
void UYggHeroAnimInstance::UpdateAimOffset()
{
	// Hero가 유효하지 않으면 실행하지 않음
	if (Hero == nullptr)
	{
		return;
	}

	// 현재 캐릭터의 조준 방향과 실제 캐릭터의 방향을 가져옴
	FRotator AimRotation = Hero->GetBaseAimRotation();
	FRotator ActorRotation = Hero->GetActorRotation();

	// 두 회전 값의 차이를 계산
	FRotator Delta = AimRotation - ActorRotation;

	// 회전 값을 정규화하여 올바른 값으로 변환
	Delta.Normalize();

	// 회전 값을 개별적으로 저장 (롤, 피치, 요)
	Roll = Delta.Roll;
	Pitch = Delta.Pitch;
	Yaw = Delta.Yaw;
}
