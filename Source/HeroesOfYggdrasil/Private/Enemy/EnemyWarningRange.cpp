// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/EnemyWarningRange.h"

// Sets default values
AEnemyWarningRange::AEnemyWarningRange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

    PrimaryActorTick.bCanEverTick = true;

    PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
    RootComponent = PlaneMesh;

}

// Called when the game starts or when spawned
void AEnemyWarningRange::BeginPlay()
{
	Super::BeginPlay();

    if (WarningMaterial != nullptr && AOEDataTable != nullptr)
    {
        FWarningAreaDataRow* Row = AOEDataTable->FindRow<FWarningAreaDataRow>(FName("BugBall"), nullptr);

        if (Row)
        {
            if (Row->PlaneMesh)
            {
                PlaneMesh->SetStaticMesh(Row->PlaneMesh);
            }

            if (Row->WarningMaterial)
            {
                DynamicMaterial = UMaterialInstanceDynamic::Create(Row->WarningMaterial, this);
                PlaneMesh->SetMaterial(0, DynamicMaterial);
            }

            Duration = Row->Duration;
            TimeElapsed = Row->TimeElapsed;
        }
    }
 
  
}

// Called every frame
void AEnemyWarningRange::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    TimeElapsed += DeltaTime;

    if (DynamicMaterial != nullptr)
    {
        float Alpha = 0.15f;
        DynamicMaterial->SetScalarParameterValue("WarningAlpha", Alpha);
    }

    if (TimeElapsed >= Duration)
    {
        Destroy();
    }
}


void AEnemyWarningRange::UpdateRange(float DeltaTime)
{
    float StartFloat = 0.0f;
    StartFloat += DeltaTime;

    float ScaleFloat = FMath::Clamp(StartFloat / Duration, 0.0f, 1.0f);
    FVector Scale = FVector{ ScaleFloat, ScaleFloat, 1.0f };

    SetActorScale3D(Scale);
}