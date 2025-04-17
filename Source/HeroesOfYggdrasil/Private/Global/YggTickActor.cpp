// Coded By AssortRock Unreal Engine Class Project

#include "Global/YggTickActor.h"

// 컴포넌트 및 관련 모듈
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"
#include "Component/ActorComponent/TickDamageComponent.h"
#include "Component/ActorComponent/TimeEventComponent.h"
#include "Component/ActorComponent/Function/TickUtilityFunctionLibrary.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

#include "Net/UnrealNetwork.h"
#include "Engine/DataTable.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Actor.h"

#include "Core/YggCharacter.h"
#include "Player/YggHero.h"
#include "Enemy/EnemyCharacter.h"

#include "Data/YggEnumData.h"

#include "Kismet/GameplayStatics.h"

#include "Particles/ParticleSystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// 상태이상 enum → 데이터 테이블 RowName으로 변환
FName ConvertStatusEnumToRowName(EStatusEffectType Type)
{
	switch (Type)
	{
	case EStatusEffectType::Poison:		return FName("Poison");
	case EStatusEffectType::Burn:		return FName("Burn");
	case EStatusEffectType::Slow:		return FName("Slow");
	case EStatusEffectType::Stunned:	return FName("Stunned");
	default:							return NAME_None;
	}
}

// 기본 생성자
AYggTickActor::AYggTickActor()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	DefualtSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));
	RootComponent = DefualtSceneRoot;

	TickDamageComponent = CreateDefaultSubobject<UTickDamageComponent>(TEXT("TickDamageComp"));
	TimeEventComponent = CreateDefaultSubobject<UTimeEventComponent>(TEXT("TimeEventComponent"));
}

// BeginPlay: 초기 이펙트 실행
void AYggTickActor::BeginPlay()
{
	Super::BeginPlay();

	TickEffectInit();
	SpawnEffect(TickDamageComponent->TargetActor);
}

// Tick: 시간 경과에 따른 상태 체크 및 삭제 처리
void AYggTickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StatusTickTime -= DeltaTime;

	if (StatusTickTime < 0.0f)
	{
		DestroyStatusTag();

		if (HasAuthority())
		{
			CleanupEffects();
			Destroy();
		}
	}
}

// EndPlay: 종료 시 이펙트 제거
void AYggTickActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	CleanupEffects();
}

void AYggTickActor::TickEffectInit()
{
	FStatusTickDataRow* DataRow = StatusTickDataTable->FindRow<FStatusTickDataRow>(StatusRowName, nullptr);

	if (DataRow)
	{
		if (DataRow->NiagaraSystem.IsValid())
		{
			NiagaraEffect = DataRow->NiagaraSystem;
		}
		if (!DataRow->Particle.IsValid())
		{
			ParticleEffect = DataRow->Particle;
		}
	}
}

// 네트워크 복제 설정
void AYggTickActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYggTickActor, TickEffectType);
	DOREPLIFETIME(AYggTickActor, NiagaraEffect);
	DOREPLIFETIME(AYggTickActor, ParticleEffect);
}

// 상태이상 태그 제거
void AYggTickActor::DestroyStatusTag()
{
	AYggCharacter* YggHero = Cast<AYggHero>(TickDamageComponent->TargetActor);
	AEnemyCharacter* YggEnemy = Cast<AEnemyCharacter>(TickDamageComponent->TargetActor);

	if (IsValid(YggHero))
	{
		FName StatusTag = FName(*("Character.DeBuff." + StatusRowName.ToString()));
		if (YggHero->GetAttributeComponent()->HasTag(StatusTag))
			YggHero->GetAttributeComponent()->RemoveTag(StatusTag);
	}
	else if (IsValid(YggEnemy))
	{
		FName StatusTag = FName(*("Enemy.DeBuff." + StatusRowName.ToString()));
		if (YggEnemy->GetAttributeComponent()->HasTag(StatusTag))
			YggEnemy->GetAttributeComponent()->RemoveTag(StatusTag);
	}
}

// 이펙트 제거
void AYggTickActor::CleanupEffects_Implementation()
{
	TArray<UActorComponent*> Components;
	GetComponents(Components);

	for (UActorComponent* Comp : Components)
	{
		if (!IsValid(Comp)) continue;

		if (auto* NiagaraComp = Cast<UNiagaraComponent>(Comp))
		{
			NiagaraComp->Deactivate();
			NiagaraComp->DestroyComponent();
		}
		else if (auto* ParticleComp = Cast<UParticleSystemComponent>(Comp))
		{
			ParticleComp->DeactivateSystem();
			ParticleComp->DestroyComponent();
		}
	}
}

// 이펙트 스폰 (히어로 / 적 구분)
void AYggTickActor::SpawnEffect_Implementation(AYggCharacter* _Target)
{
	if (!IsValid(_Target)) return;

	if (!NiagaraEffect.IsValid())
	{
		NiagaraEffect.LoadSynchronous(); // 강제 로드
	}
	if (!ParticleEffect.IsValid())
	{
		ParticleEffect.LoadSynchronous(); // 강제 로드
	}


	// Particle
	if (ParticleEffect)
	{
		UParticleSystemComponent* ParticleComp = NewObject<UParticleSystemComponent>(this);
		if (IsValid(ParticleComp))
		{
			ParticleComp->SetTemplate(ParticleEffect.Get());
			ParticleComp->bAutoActivate = true;
			ParticleComp->SetRelativeScale3D(FVector(TickActorScale, TickActorScale, TickActorScale));
			ParticleComp->RegisterComponent();
			ParticleComp->AttachToComponent(_Target->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		}
	}

	// Niagara
	if (NiagaraEffect)
	{
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			NiagaraEffect.Get(),
			_Target->GetRootComponent(),
			NAME_None,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::SnapToTarget,
			true, true
		);

		if (NiagaraComp)
		{
			NiagaraComp->SetRelativeScale3D(FVector(TickActorScale, TickActorScale, TickActorScale));
		}
	}
}

//
//// 상태이상 TickActor가 없다면 생성
//AYggTickActor* AYggTickActor::SpawnTickEffectIfNotExist(AYggCharacter* Owner, AYggCharacter* Target, EStatusEffectType InEffectType, float TickTime, float Scale)
//{
//	if (!IsValid(Target)) return nullptr;
//
//	// 이미 부착된 TickActor가 있다면 시간만 갱신
//	AYggTickActor* ExistingTickActor = UTickUtilityFunctionLibrary::FindAttachedTickActor(Target);
//	if (IsValid(ExistingTickActor))
//	{
//		FName RowName = ExistingTickActor->StatusRowName;
//		FName StatusTag;
//
//		if (Cast<AYggHero>(ExistingTickActor->TickDamageComponent->TargetActor))
//			StatusTag = FName(*("Character.DeBuff." + RowName.ToString()));
//		else if (Cast<AEnemyCharacter>(ExistingTickActor->TickDamageComponent->TargetActor))
//			StatusTag = FName(*("Enemy.DeBuff." + RowName.ToString()));
//
//		UCharacterAttributeComponent* AttrComp = Cast<AYggCharacter>(ExistingTickActor->TickDamageComponent->TargetActor)->GetAttributeComponent();
//		if (IsValid(AttrComp) && AttrComp->HasTag(StatusTag))
//		{
//			if (FStatusTickDataRow* Row = ExistingTickActor->StatusTickDataTable->FindRow<FStatusTickDataRow>(RowName, nullptr))
//				ExistingTickActor->StatusTickTime = TickTime;
//		}
//		return nullptr;
//	}
//
//	// 새 TickActor 스폰
//	FTransform SpawnTransform(Target->GetActorRotation(), Target->GetActorLocation());
//
//	TSubclassOf<AYggTickActor> TickActorBPClass = LoadClass<AYggTickActor>(nullptr, TEXT("/Script/Engine.Blueprint'/Game/Global/BP_YggTickActor.BP_YggTickActor'"));
//
//	if (!TickActorBPClass)
//	{
//		return nullptr;
//	}
//
//	AYggTickActor* TickActor = Owner->GetWorld()->SpawnActorDeferred<AYggTickActor>(TickActorBPClass, SpawnTransform, Target);
//
//
//	TickActor->TickDamageComponent->TargetActor = Target;
//	TickActor->TickDamageComponent->TickInterval = 0.5f;
//	TickActor->TickDamageComponent->DamageAmount = 0.1f;
//	TickActor->TickEffectType = InEffectType;
//	TickActor->StatusTickTime = TickTime;
//	TickActor->TickActorScale = Scale;
//	TickActor->StatusRowName = UTickUtilityFunctionLibrary::ConvertStatusEffectTypeToName(InEffectType);
//
//	FName NewRowName = TickActor->StatusRowName;
//
//
//	UGameplayStatics::FinishSpawningActor(TickActor, SpawnTransform);
//
//
//
//	// 상태이상 태그 부착
//	FName Tag = FName(*((Cast<AYggHero>(Target) ? "Character.DeBuff." : "Enemy.DeBuff.") + TickActor->StatusRowName.ToString()));
//	TickActor->Tag = Tag;
//	Target->GetAttributeComponent()->AddTag(Tag);
//
//	return TickActor;
//
//
//}
