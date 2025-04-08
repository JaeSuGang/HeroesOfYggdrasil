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

#include "Core/YggCharacter.h"
#include "Player/YggHero.h"
#include "Enemy/EnemyCharacter.h"

#include "GameFramework/Actor.h"

#include "Kismet/GameplayStatics.h"

#include "Particles/ParticleSystemComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

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


      if (IsValid(StatusTickDataTable))
	  {
		  FStatusTickDataRow* DataRow = StatusTickDataTable->FindRow<FStatusTickDataRow>(FName("Poison"), nullptr);

	      if (DataRow != nullptr)
	      {
	          TickNiagaraSystem = DataRow->NiagaraSystem;
	      }

	      if (DataRow != nullptr)
	      {
	          TickParticle = DataRow->Particle;
	      }

	      StatusTickTime = DataRow->TickTime;
	  }

	  if (TimeEventComponent)
	  {
		 CheckStatusTag();
	  }
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


void AYggTickActor::CheckStatusTag()
{

	if (!IsValid(TickDamageComponent) || !IsValid(StatusTickDataTable)) return;

	AYggCharacter* HeroTarget = Cast<AYggHero>(TickDamageComponent->TargetActor);
	if (!IsValid(HeroTarget)) return;

	AEnemyCharacter* EnemyTarget = Cast<AEnemyCharacter>(TickDamageComponent->TargetActor);

	FStatusTickDataRow* DataRow = StatusTickDataTable->FindRow<FStatusTickDataRow>(FName("Poison"), nullptr);
	if (!DataRow) return;

	if (IsValid(HeroTarget))
	{
		UCharacterAttributeComponent* HeroAttributeComponent = HeroTarget->GetAttributeComponent();

		if (HeroAttributeComponent->HasTag(TEXT("Character.DeBuff.Poision")))
		{
			AYggTickActor* AttachedTick = UTickUtilityFunctionLibrary::FindAttachedTickActor(HeroTarget);

			if (IsValid(AttachedTick) && AttachedTick != this)
			{
				AttachedTick->StatusTickTime = DataRow->TickTime;
				StatusTickTime = 0.0f;
			}

		}
		else // 히어로가 태그를 가지고 있지 않다면 태그 추가
		{
			HeroTarget->GetAttributeComponent()->AddTag(TEXT("Character.DeBuff.Poision"));
			return;
		}
	}
	else if(IsValid(EnemyTarget))
	{

	}
}

void AYggTickActor::DestroyStatusTag()
{
	AYggHero* YggHero = Cast<AYggHero>(TickDamageComponent->TargetActor);
	AEnemyCharacter* YggEnemy= Cast<AEnemyCharacter>(TickDamageComponent->TargetActor);
	
	if (IsValid(YggHero))
	{
		if (YggHero->GetAttributeComponent()->HasTag(TEXT("Character.DeBuff.Poision")))
		{
			YggHero->GetAttributeComponent()->RemoveTag(TEXT("Character.DeBuff.Poision"));
		}
	}
	else if (IsValid(YggEnemy))
	{

	}

}

AYggTickActor* FindAttachedTickActor(AYggHero* HeroTarget)
{
	if (!IsValid(HeroTarget)) return nullptr;

	TArray<AActor*> AttachedActors;
	HeroTarget->GetAttachedActors(AttachedActors);

	for (AActor* Actor : AttachedActors)
	{
		if (AYggTickActor* TickActor = Cast<AYggTickActor>(Actor))
		{
			return TickActor; 
		}
	}

	return nullptr; 
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
		_Target->GetRootComponent(),                      // 부모 컴포넌트
		NAME_None,                                       // 소켓 이름 (없을 시 NAME_None)
		FVector::ZeroVector,                             // 위치
		FRotator::ZeroRotator,                           // 회전
		EAttachLocation::KeepRelativeOffset,
		true,                                            // AutoActivate
		true                                             // AutoDestroy (중요!)
	);
	if (IsValid(NiagaraComp))
	{
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