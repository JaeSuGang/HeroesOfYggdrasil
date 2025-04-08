// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggTickActor.h"

// 캡슐 컴포넌트
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

#include "Engine/DataTable.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Component/ActorComponent/TickDamageComponent.h"
#include "Component/ActorComponent/TimeEventComponent.h"
#include "Component/ActorComponent/Function/TickUtilityFunctionLibrary.h"
#include "Components/SceneComponent.h"

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

    DefualtSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));
    TickDamageComponent = CreateDefaultSubobject<UTickDamageComponent>(TEXT("TickDamageComp"));
	TimeEventComponent = CreateDefaultSubobject<UTimeEventComponent>(TEXT("TimeEventComponent"));

}

// Called when the game starts or when spawned
void AYggTickActor::BeginPlay()
{
	Super::BeginPlay();
}

void AYggTickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StatusTickTime -= DeltaTime;

	if (StatusTickTime < 0.0f)
	{
		DestroyStatusTag();
		Destroy();
	}
}


void AYggTickActor::InitTickActor(EStatusEffectType StatusEffect)
{
	FName RowName = ConvertStatusEnumToRowName(StatusEffect);
	StatusRowName = RowName;

	if (!IsValid(StatusTickDataTable)) return;

	const FStatusTickDataRow* Row = StatusTickDataTable->FindRow<FStatusTickDataRow>(RowName, nullptr);
	if (!Row) return;

	TickParticle = Row->Particle;
	TickNiagaraSystem = Row->NiagaraSystem;
	StatusTickTime = Row->TickTime;
}


void AYggTickActor::DestroyStatusTag()
{
	AYggCharacter* YggHero = Cast<AYggHero>(TickDamageComponent->TargetActor);
	AEnemyCharacter* YggEnemy= Cast<AEnemyCharacter>(TickDamageComponent->TargetActor);
	
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

		if (YggHero->GetAttributeComponent()->HasTag(StatusTag))
		{
			YggHero->GetAttributeComponent()->RemoveTag(StatusTag);
		}
	}

}


void AYggTickActor::SetTickDamage(AYggCharacter* _Target, float _Interval, float DamageAmount)
{
	if (!IsValid(_Target)) return;

	// 데미지 설정
	TickDamageComponent->TargetActor = _Target;
	TickDamageComponent->TickInterval = _Interval;
	TickDamageComponent->DamageAmount = DamageAmount;


	

	UParticleSystemComponent* ParticleComp = NewObject<UParticleSystemComponent>(this);
	if (IsValid(ParticleComp))
	{
		ParticleComp->SetTemplate(TickParticle.Get());
		ParticleComp->bAutoActivate = true;
		
		ParticleComp->SetRelativeScale3D(FVector(10.0f));

		ParticleComp->RegisterComponent();

		ParticleComp->AttachToComponent(
			_Target->GetRootComponent(),
			FAttachmentTransformRules::KeepRelativeTransform
		);
	}
	else
	{
		TickParticle.LoadSynchronous();
	}

	UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
		TickNiagaraSystem.Get(),                         // TSoftObjectPtr or UNiagaraSystem*
		GetRootComponent(),								 // 부모 컴포넌트
		NAME_None,                                       // 소켓 이름 (없을 시 NAME_None)
		FVector::ZeroVector,                             // 위치
		FRotator::ZeroRotator,                           // 회전
		EAttachLocation::KeepRelativeOffset,
		true,                                            // AutoActivate
		true                                             // AutoDestroy (중요!)
	);

	if (IsValid(NiagaraComp))
	{
		NiagaraComp->AttachToComponent(_Target->GetCapsuleComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		NiagaraComp->SetRelativeScale3D(FVector(10.0f));
	}
	else
	{
		TickNiagaraSystem.LoadSynchronous();;
	}
		
}


void AYggTickActor::DisableAllComponents()
{
	TArray<UActorComponent*> Components;
	GetComponents(Components);

	for (UActorComponent* Comp : Components)
	{
		if (!IsValid(Comp)) continue;

		// Tick 끄기
		Comp->SetComponentTickEnabled(false);

		// 활성 상태 비활성화 (렌더/이펙트 등)
		if (UPrimitiveComponent* PrimComp = Cast<UPrimitiveComponent>(Comp))
		{
			PrimComp->SetVisibility(false);
			PrimComp->SetActive(false);
			PrimComp->Deactivate();
		}
		else if (UParticleSystemComponent* ParticleComp = Cast<UParticleSystemComponent>(Comp))
		{
			ParticleComp->DeactivateSystem();
		}
		else
		{
			Comp->Deactivate(); // 나머지 일반 컴포넌트
		}
	}
}


AYggTickActor* AYggTickActor::SpawnTickEffectIfNotExist(
	UObject* WorldContext,
	AYggCharacter* Target,
	TSubclassOf<AYggTickActor> TickActorClass,
	EStatusEffectType EffectType,
	float TickInterval,
	float DamagePerTick
)
{
	if (!WorldContext || !IsValid(Target) || !TickActorClass) return nullptr;

	

	// 이미 부착된 상태이상 체크
	AYggTickActor* ExistingTickActor = UTickUtilityFunctionLibrary::FindAttachedTickActor(Target);
	if (IsValid(ExistingTickActor))
	{	
		AYggCharacter* HeroTarget = Cast<AYggHero>(ExistingTickActor->TickDamageComponent->TargetActor);
		AEnemyCharacter* EnemyTarget = Cast<AEnemyCharacter>(ExistingTickActor->TickDamageComponent->TargetActor);
		FName RowName = ConvertStatusEnumToRowName(EffectType);

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
					ExistingTickActor->StatusTickTime = ExistingStatusRow->TickTime;
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
					ExistingTickActor->StatusTickTime = ExistingStatusRow->TickTime;
				}
			}

		}


		
		return nullptr;
	}



	// Spawn
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContext);
	FTransform SpawnTransform(Target->GetActorRotation(), Target->GetActorLocation());

	AYggTickActor* TickActor = World->SpawnActorDeferred<AYggTickActor>(
		TickActorClass,
		SpawnTransform,
		nullptr,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if (!IsValid(TickActor)) return nullptr;

	// 데미지 및 상태 설정
	TickActor->SetTickDamage(Target, TickInterval, DamagePerTick);
	TickActor->InitTickActor(EffectType);
	
	if (AYggCharacter* Hero = Cast<AYggHero>(TickActor->TickDamageComponent->TargetActor))
	{
		if (IsValid(Hero))
		{
			TickActor->Tag = FName(*("Character.DeBuff." + ConvertStatusEnumToRowName(EffectType).ToString()));
			Hero->GetAttributeComponent()->AddTag(TickActor->Tag);
			UGameplayStatics::FinishSpawningActor(TickActor, SpawnTransform);
			
		}
	}
	else if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(TickActor->TickDamageComponent->TargetActor))
	{
		if (IsValid(Enemy))
		{
			TickActor->Tag = FName(*("Enemy.DeBuff." + ConvertStatusEnumToRowName(EffectType).ToString()));
			Enemy->GetAttributeComponent()->AddTag(TickActor->Tag);
			UGameplayStatics::FinishSpawningActor(TickActor, SpawnTransform);
		}
	}

	return TickActor;
}
