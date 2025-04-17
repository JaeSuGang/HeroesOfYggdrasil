// Coded By AssortRock Unreal Engine Class Project


#include "Component/MHPBarComponent.h"

#include "MainGame/UI/YggMHPBarUserWidget.h"
#include "Components/WidgetComponent.h"

#include "Attribute/CharacterAttributeComponent.h"
#include "Enemy/EnemyCharacter.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMHPBarComponent::UMHPBarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UMHPBarComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	MHPBarWidgetComponent = NewObject<UWidgetComponent>(this, UWidgetComponent::StaticClass());
	MHPBarWidgetComponent->RegisterComponent();
	MHPBarWidgetComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	MHPBarWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	MHPBarWidgetComponent->SetDrawSize(FVector2D(100.0f, 10.0f));
	MHPBarWidgetComponent->SetPivot(FVector2D(0.5f, 0.0f));
	MHPBarWidgetComponent->SetIsReplicated(true);

	MHPBarWidget = CreateWidget<UYggMHPBarUserWidget>(GetWorld(), MHPBarWidgetClass);
	

	MHPBarWidgetComponent->SetWidget(MHPBarWidget);


}

// Called every frame
void UMHPBarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (APlayerCameraManager* Cam = UGameplayStatics::GetPlayerCameraManager(this, 0))
	{
		FVector CamLoc = Cam->GetCameraLocation();
		FVector ToCam = CamLoc - MHPBarWidgetComponent->GetComponentLocation();
		FRotator LookAtRot = FRotationMatrix::MakeFromX(ToCam).Rotator();
		LookAtRot.Pitch = 0.0f;
		MHPBarWidgetComponent->SetWorldRotation(LookAtRot);
	}
}

void UMHPBarComponent::UpdateHPBarWidgetToAll_Implementation(float HP)
{
	if (MHPBarWidget)
	{
		MHPBarWidget->UpdateHPBar();
	}
}

void UMHPBarComponent::OnStatusChanged()
{
	if (IsValid(MHPBarWidget))
	{
		MHPBarWidget->UpdateHPBar();
	}
}

void UMHPBarComponent::Init(AEnemyCharacter* Enemy)
{
	if (IsValid(Enemy))
	{
		EnemyCharacter = Enemy;

		MHPBarWidget->SetAttachedCharacter(EnemyCharacter);
		
		if (IsValid(MHPBarWidget))
		{
			MHPBarWidget->CAC->ServerDelegate_OnTakeDamage.AddDynamic(this, &UMHPBarComponent::UpdateHPBarWidgetToAll);
			MHPBarWidget->CAC->ClientDelegate_OnStatusChanged.AddDynamic(this, &UMHPBarComponent::OnStatusChanged);
		}
	}
}