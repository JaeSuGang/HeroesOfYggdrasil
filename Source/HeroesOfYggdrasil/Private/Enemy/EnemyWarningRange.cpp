// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/EnemyWarningRange.h"

#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

#include "Global/YggTickActor.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Player/YggHero.h"
#include "Enemy/EnemyCharacter.h"

// Sets default values
AEnemyWarningRange::AEnemyWarningRange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

    PrimaryActorTick.bCanEverTick = true;

    PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
    RootComponent = PlaneMesh;
    
    
    {
        bReplicates = true;
        SetReplicateMovement(true);
    }

    {
        RangeAttackCollision = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("CapsuleCollision"));
        RangeAttackCollision->SetupAttachment(PlaneMesh);
        RangeAttackCollision->CollisionOff();
        RangeAttackCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyWarningRange::OverLap);
    }


}

// Called when the game starts or when spawned
void AEnemyWarningRange::BeginPlay()
{
    Super::BeginPlay();

    YggCharacterEnemy = Cast<AEnemyCharacter>(GetOwner());
    InitializeWarningRange();
}

void AEnemyWarningRange::InitializeWarningRange()
{
    if (!IsValid(YggCharacterEnemy)) return;

    DataKeyString = YggCharacterEnemy->GetDataKey();
    FName DataName = GetMeshNameByKey(DataKeyString);
    FWarningAreaDataRow* Row = AOEDataTable->FindRow<FWarningAreaDataRow>(DataName, nullptr);

    if (WarningMaterial && AOEDataTable && Row)
    {
        if (Row->PlaneMesh) PlaneMesh->SetStaticMesh(Row->PlaneMesh);
        if (Row->WarningMaterial)
        {
            DynamicMaterial = UMaterialInstanceDynamic::Create(Row->WarningMaterial, this);
            PlaneMesh->SetMaterial(0, DynamicMaterial);
        }

        Duration = Row->Duration;
        TimeElapsed = Row->TimeElapsed;
        SetActorScale3D(Row->ScaleVector);
        EffectParticle = Row->RangeEffectParticle;
        EnemyNiagaraSystem = Row->NiagaraEffectSystem;

        if (DynamicMaterial) DynamicMaterial->SetScalarParameterValue("WarningAlpha", 0.2f);
    }
}

// Called every frame
void AEnemyWarningRange::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    if (!IsValid(YggCharacterEnemy)) return;

    TimeElapsed += DeltaTime;

    ChangeArea();

    if (TimeElapsed > Duration)
    {
        SpawnRangeEffect();
        RangeAttackCollision->SetCapsuleSize(100.0f, 100.0f);
        RangeAttackCollision->CollisionOn();
        Destroy();
        return;
    }
}

void AEnemyWarningRange::SpawnRangeEffect_Implementation()
{
    if (IsValid(YggCharacterEnemy))
    {
        DataKeyString = YggCharacterEnemy->GetDataKey();
    }

    FName DataName = GetMeshNameByKey(DataKeyString);
    FWarningAreaDataRow* Row = AOEDataTable->FindRow<FWarningAreaDataRow>(DataName, nullptr);

    if (!Row) return;

    if (IsValid(EffectParticle))
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            EffectParticle,
            GetActorLocation(),
            GetActorRotation(),
            FVector(Row->EffectScaleFloat),
            true
        );
    }

    if (IsValid(EnemyNiagaraSystem))
    {
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            EnemyNiagaraSystem,
            GetActorLocation(),
            GetActorRotation(),
            FVector(Row->EffectScaleFloat),
            true
        );
    }
}

void AEnemyWarningRange::ChangeArea()
{
    if (IsValid(YggCharacterEnemy))
    {
        DataKeyString = YggCharacterEnemy->GetDataKey();
    }

    FName DataName = GetMeshNameByKey(DataKeyString);

    FWarningAreaDataRow* Row = AOEDataTable->FindRow<FWarningAreaDataRow>(DataName, nullptr);
    
    if (Row != nullptr)
    {
        float Progress = FMath::Clamp(TimeElapsed / Duration, 0.0f, 1.0f);

        FVector TargetScale = Row->ScaleVector;
        
        SetActorScale3D(TargetScale * Progress);
    }
    
}


void AEnemyWarningRange::HideAllComponents()
{
    TArray<UActorComponent*> Components;
    GetComponents(Components);

    for (UActorComponent* Comp : Components)
    {
        if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(Comp))
        {
            Prim->SetVisibility(false, true);  
        }
    }
}

void AEnemyWarningRange::OverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (IsValid(OtherActor))
    {
        AYggHero* Hero = Cast<AYggHero>(OtherActor);

        if (IsValid(Hero))
        {
            if (Hero)
            {
                if (IsValid(YggCharacterEnemy))
                {

                    AYggCharacter* YggCharacter = Cast<AYggCharacter>(Hero);
                    YggCharacterEnemy->OnHeroEnteredRange.Broadcast(YggCharacter);
                }
                
            }
        }
    }
}

void AEnemyWarningRange::SetCollisionOwnerEnemy(AEnemyCharacter* _Enemy)
{
    if (IsValid(_Enemy))
    {
        YggCharacterEnemy = _Enemy;
        RangeAttackCollision->SetOwnerCharacter(YggCharacterEnemy);
    }
}

FName AEnemyWarningRange::GetMeshNameByKey(const FString& _DataString)
{
    static const TMap<FString, FName> SectionMap = {
        {TEXT("Minion_Witch_0"), FName("Poison")},
        {TEXT("Minion_Witch_1"), FName("Snow")},
        {TEXT("Minion_Witch_2"), FName("Lightning")},
        {TEXT("Minion_Witch_3"), FName("Fire")},
        {TEXT("Dragon"), FName("Explosion")}
    };

    if (const FName* Found = SectionMap.Find(_DataString))
    {
        return *Found;
    }

    return FName("Poison");
}