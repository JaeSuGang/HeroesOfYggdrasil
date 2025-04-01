// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/YggParticleNotify.h"

#include "Kismet/GameplayStatics.h"

// Particle
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Niagara
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

// Hero
#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Data/YggStructData.h"

// Enermy
#include "Enemy/EnemyCharacter.h"
#include "Attribute/EnemyAttributeComponent.h"

void UYggParticleNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner())) return;

	if (!IsValid(PSTemplate) && !IsValid(NSTemplate)) return;

	if (AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner()))
	{
		UHeroAttributeComponent* AttrComp = Hero->GetHeroAttributeComponent();
		if (!IsValid(AttrComp)) return;

		if (!Skills.SkillQ && !Skills.SkillE && !Skills.SkillR) return;

		if (Skills.SkillQ)
		{
			Duration = AttrComp->SkillQMaxContinueTime;
		}
		else if (Skills.SkillE)
		{
			Duration = AttrComp->SkillEMaxContinueTime;
		}
		else if (Skills.SkillR)
		{
			Duration = AttrComp->SkillRMaxContinueTime;
		}
	}
	else if (AEnemyCharacter* Enemy = Cast< AEnemyCharacter>(MeshComp->GetOwner()))
	{
		UEnemyAttributeComponent* EAttrComp = Enemy->GetEnemyAttributeComponent();
		if (!IsValid(EAttrComp)) return;

		// Enemy Duration 가져오기.
	}

	// YggParticleNotify.cpp
	if (PSTemplate)
	{
		UParticleSystemComponent* PSC = UGameplayStatics::SpawnEmitterAttached(
			PSTemplate,
			MeshComp,
			NAME_None,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::SnapToTarget,
			true
		);

		if (PSC && DelayedPSTemplate) // DelayedPSTemplate이 유효한지 확인
		{
			// 2초 후 15초 지속 파티클 스폰
			FTimerHandle TimerHandle;
			PSC->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, MeshComp]()
			{
				if (IsValid(MeshComp))
				{
					UGameplayStatics::SpawnEmitterAttached(
						DelayedPSTemplate, // 15초 파티클
						MeshComp,
						NAME_None,
						FVector::ZeroVector,
						FRotator::ZeroRotator,
						EAttachLocation::SnapToTarget,
						true
					);
				}
			}, 2.0f, false); // 2초 딜레이
		}
	}
	else if (NSTemplate)
	{
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
			NSTemplate,            // 사용할 나이아가라 템플릿
			MeshComp,              // 부착 대상
			NAME_None,             // 소켓 이름 (필요 시 변경)
			FVector::ZeroVector,   // 상대 위치
			FRotator::ZeroRotator, // 상대 회전
			EAttachLocation::SnapToTarget,
			true                   // 인스턴스화 후 자동 파괴
		);

		if (NiagaraComp)
		{
			FTimerHandle TimerHandle;
			NiagaraComp->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, NiagaraComp]()
			{
				NiagaraComp->SetFloatParameter(FName("EmitterDuration"), this->Duration);
			}, DelayTime, false);
		}
	}
}

#if WITH_EDITOR
void UYggParticleNotify::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropName = PropertyChangedEvent.GetPropertyName();

	if (PropName == GET_MEMBER_NAME_CHECKED(FSkills, SkillQ) && Skills.SkillQ)
	{
		Skills.SkillE = false;
		Skills.SkillR = false;
	}
	else if (PropName == GET_MEMBER_NAME_CHECKED(FSkills, SkillE) && Skills.SkillE)
	{
		Skills.SkillQ = false;
		Skills.SkillR = false;
	}
	else if (PropName == GET_MEMBER_NAME_CHECKED(FSkills, SkillR) && Skills.SkillR)
	{
		Skills.SkillQ = false;
		Skills.SkillE = false;
	}

	if (PropName == GET_MEMBER_NAME_CHECKED(UYggParticleNotify, PSTemplate) && PSTemplate)
	{
		NSTemplate = nullptr;
	}
	else if (PropName == GET_MEMBER_NAME_CHECKED(UYggParticleNotify, NSTemplate) && NSTemplate)
	{
		PSTemplate = nullptr;
	}
}
#endif
