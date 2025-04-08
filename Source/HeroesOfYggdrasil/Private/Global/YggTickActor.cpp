// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggTickActor.h"

// 캡슐 컴포넌트
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

#include "Engine/DataTable.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Component/ActorComponent/TickDamageComponent.h"

#include "Core/YggCharacter.h"

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
}

// Called when the game starts or when spawned
void AYggTickActor::BeginPlay()
{
	Super::BeginPlay();


      if (IsValid(StatusTickDataTable))
    {
        FStatusTickDataRow* Row = StatusTickDataTable->FindRow<FStatusTickDataRow>(FName("Poison"), nullptr);

        if (Row != nullptr)
        {
            TickNiagaraSystem = Row->NiagaraSystem;
        }

        if (Row != nullptr)
        {
            TickParticle = Row->Particle;
        }

        StatusTickTime = Row->TickTime;
    }

}

void AYggTickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    StatusTickTime -= DeltaTime;

    if (StatusTickTime < 0.0f)
    {
        Destroy();
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
