// Coded By AssortRock Unreal Engine Class Project


#include "Component/MHPBarComponent.h"

#include "MainGame/UI/YggMHPBarUserWidget.h"
#include "Components/WidgetComponent.h"

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

	MHPBarWidget = CreateWidget<UYggMHPBarUserWidget>(GetWorld(), MHPBarWidgetClass);
	MHPBarWidget->SetAttachedCharacter(EnemyCharacter);

	MHPBarWidgetComponent->SetWidget(MHPBarWidget);
}


// Called every frame
void UMHPBarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//if (APlayerCameraManager* Cam = UGameplayStatics::GetPlayerCameraManager(this, 0))
	//{
	//	FVector CamLoc = Cam->GetCameraLocation();
	//	FVector ToCam = CamLoc - WidgetComponent->GetComponentLocation();
	//	FRotator LookAtRot = FRotationMatrix::MakeFromX(ToCam).Rotator();
	//	LookAtRot.Pitch = 0.0f;
	//	WidgetComponent->SetWorldRotation(LookAtRot);
	//}
}

