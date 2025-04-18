// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggTickActor.h"

// 캡슐 컴포넌트
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

#include "Net/UnrealNetwork.h"
#include "Engine/DataTable.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Component/ActorComponent/TickDamageComponent.h"
#include "Component/ActorComponent/TimeEventComponent.h"
#include "Component/ActorComponent/Function/TickUtilityFunctionLibrary.h"
#include "Components/SceneComponent.h"

#include "Data/YggEnumData.h"

#include "Core/YggCharacter.h"
#include "Player/YggHero.h"
#include "Enemy/EnemyCharacter.h"

#include "GameFramework/Actor.h"

#include "Kismet/GameplayStatics.h"

#include "Particles/ParticleSystemComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"






FName ConvertStatusEnumToRowName(EStatusEffectType Type)
{
	switch (Type)
	{
	case EStatusEffectType::Poison:		return FName("Poison");
	case EStatusEffectType::Burn:		return FName("Burn");
	case EStatusEffectType::Slow:		return FName("Slow");
	case EStatusEffectType::Stunned:	return FName("Stunned");
	default:                        return NAME_None;
	}
}

// Sets default values
AYggTickActor::AYggTickActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	DefualtSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));
	RootComponent = DefualtSceneRoot;
	TickDamageComponent = CreateDefaultSubobject<UTickDamageComponent>(TEXT("TickDamageComp"));
	TimeEventComponent = CreateDefaultSubobject<UTimeEventComponent>(TEXT("TimeEventComponent"));

}

// Called when the game starts or when spawned
void AYggTickActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) {
		//LoadEffectFromDataTable(); // Replicated 전에 서버에서만 로드
		SpawnEffect(TickDamageComponent->TargetActor);
	}
	
}

void AYggTickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StatusTickTime -= DeltaTime;

	if (StatusTickTime < 0.0f || TickDamageComponent->TargetActor->GetAttributeComponent()->HasTag(TEXT("Character.State.Death")))
	{
		DestroyStatusTag();

		if (HasAuthority()) // 반드시 서버만 호출
		{
			CleanupEffects();
			Destroy();
		}
	}
}

void AYggTickActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{

	Super::EndPlay(EndPlayReason);
	CleanupEffects();
}

void AYggTickActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYggTickActor, TickNiagaraSystem);
	DOREPLIFETIME(AYggTickActor, TickParticle);
}

void AYggTickActor::LoadEffectFromDataTable()
{
	FName RowName = ConvertStatusEnumToRowName(TickEffectType);
	StatusRowName = RowName;


	TSoftObjectPtr<UDataTable> TableRef = TSoftObjectPtr<UDataTable>(
		FSoftObjectPath("/Game/Data/StatusTickActorDataTable.StatusTickActorDataTable"));

	if (!TableRef.IsValid())
	{
		TableRef.LoadSynchronous();
	}

	StatusTickDataTable = TableRef.Get();

	if (StatusTickDataTable)
	{
		if (const FStatusTickDataRow* Row = StatusTickDataTable->FindRow<FStatusTickDataRow>(RowName, nullptr))
		{
			TickParticle = Row->Particle;
			TickNiagaraSystem = Row->NiagaraSystem;
		}
	}
}

void AYggTickActor::DestroyStatusTag()
{
	AYggCharacter* YggHero = Cast<AYggHero>(TickDamageComponent->TargetActor);
	AEnemyCharacter* YggEnemy = Cast<AEnemyCharacter>(TickDamageComponent->TargetActor);

	if (IsValid(YggHero))
	{
		FName StatusTag = FName(*("Character.DeBuff." + StatusRowName.ToString()));

		if (YggHero->GetAttributeComponent()->HasTag(StatusTag))
		{
			YggHero->GetAttributeComponent()->RemoveTag(StatusTag);
		}
	}
	else if (IsValid(YggEnemy))
	{
		FName StatusTag = FName(*("Enemy.DeBuff." + StatusRowName.ToString()));

		if (YggEnemy->GetAttributeComponent()->HasTag(StatusTag))
		{
			YggEnemy->GetAttributeComponent()->RemoveTag(StatusTag);
		}
	}

}


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



void AYggTickActor::SpawnEffect_Implementation(AYggCharacter* _Target)
{
	if (!IsValid(_Target)) return;

	if (!TickNiagaraSystem.IsValid())
	{
		TickNiagaraSystem.LoadSynchronous(); // 강제 로드
	}
	if (!TickParticle.IsValid())
	{
		TickParticle.LoadSynchronous(); // 강제 로드
	}

	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(_Target);
	AYggHero* Hero = Cast<AYggHero>(_Target);

	if (!IsValid(Hero) && !IsValid(Enemy))
	{
		return;
	}

	if (IsValid(Hero))
	{

		// ParticleSystemComponent
		if (TickParticle.IsValid())
		{
			UParticleSystemComponent* ParticleComp = NewObject<UParticleSystemComponent>(this);
			if (IsValid(ParticleComp))
			{
				ParticleComp->SetTemplate(TickParticle.Get());
				ParticleComp->bAutoActivate = true;
				ParticleComp->SetRelativeScale3D(FVector(1.0f));
				ParticleComp->RegisterComponent();
				ParticleComp->AttachToComponent(Hero->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
			}
		}

		// NiagaraComponent
		if (TickNiagaraSystem.IsValid())
		{
			UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
				TickNiagaraSystem.Get(),
				Hero->GetRootComponent(),           // 또는 CapsuleComponent 등 중심 컴포넌트
				TEXT("butt_cloth_l_01"),
				FVector::ZeroVector,                   // 타겟 중심
				FRotator::ZeroRotator,
				EAttachLocation::SnapToTarget,         // 정확히 중심에 부착
				true, true
			);

			if (IsValid(NiagaraComp))
			{
				NiagaraComp->SetRelativeScale3D(FVector(1.0f));  // 시각적 조정
			}
		}
	}
	else
	{
		if (IsValid(Enemy))
		{

			// ParticleSystemComponent
			if (TickParticle.IsValid())
			{
				UParticleSystemComponent* ParticleComp = NewObject<UParticleSystemComponent>(this);
				if (IsValid(ParticleComp))
				{
					ParticleComp->SetTemplate(TickParticle.Get());
					ParticleComp->bAutoActivate = true;
					ParticleComp->SetRelativeScale3D(FVector(1.0f));
					ParticleComp->RegisterComponent();
					ParticleComp->AttachToComponent(Enemy->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
				}
			}

			// NiagaraComponent
			if (TickNiagaraSystem.IsValid())
			{
				UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
					TickNiagaraSystem.Get(),
					Enemy->GetRootComponent(),           // 또는 CapsuleComponent 등 중심 컴포넌트
					NAME_None,
					FVector::ZeroVector,                   // 타겟 중심
					FRotator::ZeroRotator,
					EAttachLocation::SnapToTarget,         // 정확히 중심에 부착
					true, true
				);

				if (IsValid(NiagaraComp))
				{
					NiagaraComp->SetRelativeScale3D(FVector(1.0f));  // 시각적 조정
				}
			}
		}
	}
}


// 공격 캐릭터 , 타겟 캐릭터, EStatusEffectType(YggEnum), 데미지, 간격, 공격 시간
AYggTickActor* AYggTickActor::SpawnTickEffectIfNotExist(AYggCharacter* Owner, AYggCharacter* Target, EStatusEffectType EffectType, float TickDamage,float Interval, float TickTime)
{
	if (!IsValid(Target)) return nullptr;



	// 이미 부착된 상태이상 체크
	AYggTickActor* ExistingTickActor = UTickUtilityFunctionLibrary::FindAttachedTickActor(Target);
	if (IsValid(ExistingTickActor))
	{
		AYggCharacter* HeroTarget = Cast<AYggHero>(ExistingTickActor->TickDamageComponent->TargetActor);
		AEnemyCharacter* EnemyTarget = Cast<AEnemyCharacter>(ExistingTickActor->TickDamageComponent->TargetActor);
		FName RowName = ExistingTickActor->StatusRowName;

		if (IsValid(HeroTarget))
		{
			UCharacterAttributeComponent* HeroAttributeComponent = HeroTarget->GetAttributeComponent();

			if (!IsValid(HeroAttributeComponent))
			{
				return nullptr;
			}

			FName StatusTag = FName(*("Character.DeBuff." + RowName.ToString()));

			if (HeroAttributeComponent->HasTag(StatusTag))
			{
				if (FStatusTickDataRow* ExistingStatusRow = ExistingTickActor->StatusTickDataTable->FindRow<FStatusTickDataRow>(RowName, nullptr))
				{
					ExistingTickActor->DestroyStatusTag();
					HeroAttributeComponent->AddTag(StatusTag);
					ExistingTickActor->StatusTickTime = TickTime;
				}
			}
		}
		else if (IsValid(EnemyTarget))
		{
			UCharacterAttributeComponent* EnemyAttributeComponent = EnemyTarget->GetAttributeComponent();

			if (!IsValid(EnemyAttributeComponent))
			{
				return nullptr;
			}

			FName StatusTag = FName(*("Enemy.DeBuff." + RowName.ToString()));

			if (EnemyAttributeComponent->HasTag(StatusTag))
			{
				if (FStatusTickDataRow* ExistingStatusRow = ExistingTickActor->StatusTickDataTable->FindRow<FStatusTickDataRow>(RowName, nullptr))
				{
					ExistingTickActor->DestroyStatusTag();
					EnemyAttributeComponent->AddTag(StatusTag);
					ExistingTickActor->StatusTickTime = TickTime;
				}
			}

		}



		return nullptr;
	}



	// Spawn
	FTransform SpawnTransform(Target->GetActorRotation(), Target->GetActorLocation());

	AYggTickActor* TickActor = Owner->GetWorld()->SpawnActorDeferred<AYggTickActor>(AYggTickActor::StaticClass(), SpawnTransform, Target);

	TickActor->TickDamageComponent->TargetActor = Target;
	TickActor->TickDamageComponent->TickInterval = Interval;
	TickActor->TickDamageComponent->DamageAmount = TickDamage;
	TickActor->StatusTickTime = TickTime;
	TickActor->TickEffectType = EffectType;
	TickActor->LoadEffectFromDataTable(); // Replicated 전에 서버에서만 로드

	AEnemyCharacter* OwnerEnemy = Cast<AEnemyCharacter>(Owner);
	AYggHero* OwnerHero = Cast<AYggHero>(Owner);

	UGameplayStatics::FinishSpawningActor(TickActor, SpawnTransform);

	if (AYggCharacter* Hero = Cast<AYggHero>(TickActor->TickDamageComponent->TargetActor))
	{
		if (IsValid(Hero))
		{
			TickActor->Tag = FName(*("Character.DeBuff." + TickActor->StatusRowName.ToString()));
			Hero->GetAttributeComponent()->AddTag(TickActor->Tag);
		}
	}
	else if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(TickActor->TickDamageComponent->TargetActor))
	{
		if (IsValid(Enemy))
		{
			TickActor->Tag = FName(*("Enemy.DeBuff." + TickActor->StatusRowName.ToString()));
			Enemy->GetAttributeComponent()->AddTag(TickActor->Tag);
		}
	}

	return TickActor;
}

