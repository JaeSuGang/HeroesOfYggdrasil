// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/YggParticleNotify.h"

#include "Kismet/GameplayStatics.h"

// Particle
#include "Particles/Emitter.h"
#include "Particles/ParticleEmitter.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleLODLevel.h"
#include "Particles/ParticleModuleRequired.h"

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

	if (PSTemplate)
	{
		UParticleSystemComponent* PSComp = UGameplayStatics::SpawnEmitterAttached(
			PSTemplate,
			MeshComp,
			NAME_None,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::SnapToTarget,
			true
		);

		DisableOtherEmitters(PSComp, Emitters);

		FTimerHandle TimerHandle;
		PSComp->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, PSComp]()
		{
			EndParticle(PSComp, Emitters);
		}, Duration, false);
	}
	else if (NSTemplate)
	{
		//UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
		//	NSTemplate,            // 사용할 나이아가라 템플릿
		//	MeshComp,              // 부착 대상
		//	NAME_None,             // 소켓 이름 (필요 시 변경)
		//	FVector::ZeroVector,   // 상대 위치
		//	FRotator::ZeroRotator, // 상대 회전
		//	EAttachLocation::SnapToTarget,
		//	true                   // 인스턴스화 후 자동 파괴
		//);

		//if (NiagaraComp)
		//{
		//	FTimerHandle TimerHandle;
		//	NiagaraComp->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, NiagaraComp]()
		//	{
		//		NiagaraComp->SetFloatParameter(FName("EmitterDuration"), this->Duration);
		//	}, DelayTime, false);
		//}
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

void UYggParticleNotify::DisableOtherEmitters(UParticleSystemComponent* PSComp, const TArray<FString>& EmittersToDisable)
{
	if (!IsValid(PSComp) || !IsValid(PSComp->Template)) return;

	// PSComp의 템플릿에서 각 Emitter를 순회합니다.
	for (UParticleEmitter* Emitter : PSComp->Template->Emitters)
	{
		if (!Emitter)
		{
			continue;
		}

		FName EmitterFName = Emitter->GetEmitterName();

		// EmittersToDisable에 포함되어 있다면 활성화, 아니면 비활성화.
		bool bShouldEnable = EmittersToDisable.Contains(EmitterFName.ToString());
		PSComp->SetEmitterEnable(EmitterFName, bShouldEnable);
	}
}

void UYggParticleNotify::EndParticle(UParticleSystemComponent* PSComp, const TArray<FString>& EmittersToDisable)
{
	if (!IsValid(PSComp) || !IsValid(PSComp->Template)) return;

	float ActiveEmitterDuration = 0.0f;

	// PSComp의 템플릿에서 각 Emitter를 순회.
	for (UParticleEmitter* Emitter : PSComp->Template->Emitters)
	{
		if (!Emitter)
		{
			continue;
		}

		FName EmitterFName = Emitter->GetEmitterName();

		// EmittersToDisable에 포함되어 있다면 비활성화, 아니면 활성화.
		bool bShouldEnable = !EmittersToDisable.Contains(EmitterFName.ToString());
		PSComp->SetEmitterEnable(EmitterFName, bShouldEnable);

		// 활성화 되어있는 Emitter의 LODLevel 0의 EmitterDuration을 Get.
		if (bShouldEnable && Emitter->LODLevels.Num() > 0)
		{
			UParticleLODLevel* LODLevel = Emitter->LODLevels[0];
			if (LODLevel && LODLevel->RequiredModule)
			{
				float GettedDuration = LODLevel->RequiredModule->EmitterDuration;
				ActiveEmitterDuration = FMath::Max(ActiveEmitterDuration, GettedDuration);
			}
		}

		// ActiveEmitterDuration이후로 종료.
		FTimerHandle TimerHandle;
		PSComp->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [EmitterFName, PSComp]()
		{
			PSComp->SetEmitterEnable(EmitterFName, false);
		}, ActiveEmitterDuration, false);
	}
}