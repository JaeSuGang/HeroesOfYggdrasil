// Coded By AssortRock Unreal Engine Class Project


#include "Component/NicknameBarComponent.h"

#include "MainGame/UI/YggNicknameBarUserWidget.h"
#include "MainGame/StageManager.h"

#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UNicknameBarComponent::UNicknameBarComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	//NicknameBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NicknameBarWidget"));
	//NicknameBarWidgetComponent->SetupAttachment(this);
	////NicknameBarWidgetComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	//NicknameBarWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	//NicknameBarWidgetComponent->SetDrawSize(FVector2D(100.0f, 10.0f));
	//NicknameBarWidgetComponent->SetPivot(FVector2D(0.5f, 0.0f));
}


// Called when the game starts
void UNicknameBarComponent::BeginPlay()
{
	Super::BeginPlay();

	NicknameBarWidgetComponent = NewObject<UWidgetComponent>(this, UWidgetComponent::StaticClass());
	NicknameBarWidgetComponent->RegisterComponent();
	NicknameBarWidgetComponent->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	NicknameBarWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	NicknameBarWidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f));
	NicknameBarWidgetComponent->SetPivot(FVector2D(0.5f, 0.0f));

	if (!NicknameBarWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);
	NicknameBarWidget = CreateWidget<UYggNicknameBarUserWidget>(GetWorld(), NicknameBarWidgetClass);
	NicknameBarWidget->NicknameBarComponent = this;

	NicknameBarWidget->SetPlayerName();

	//AStageManager* SM = AStageManager::Get(GetWorld());
	//if (IsValid(SM))
	//{
	//	SM->OnSetNickname.RemoveDynamic(NicknameBarWidget, &UYggNicknameBarUserWidget::SetPlayerName);
	//
	//	SM->OnSetNickname.AddDynamic(NicknameBarWidget, &UYggNicknameBarUserWidget::SetPlayerName);
	//}

	NicknameBarWidgetComponent->SetWidget(NicknameBarWidget);
}


// Called every frame
void UNicknameBarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (APlayerCameraManager* Cam = UGameplayStatics::GetPlayerCameraManager(this, 0))
	{
		FVector CamLoc = Cam->GetCameraLocation();
		FVector ToCam = CamLoc - NicknameBarWidgetComponent->GetComponentLocation();
		FRotator LookAtRot = FRotationMatrix::MakeFromX(ToCam).Rotator();
		LookAtRot.Pitch = 0.0f;
		NicknameBarWidgetComponent->SetWorldRotation(LookAtRot);
	}
}

