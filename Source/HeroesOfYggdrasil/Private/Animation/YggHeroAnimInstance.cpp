// Coded By AssortRock Unreal Engine Class Project


#include "Animation/YggHeroAnimInstance.h"

#include "Player/YggHero.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UYggHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Hero = Cast<AYggHero>(TryGetPawnOwner());
	if (Hero == nullptr)
	{
		return;
	}
	CharacterMovementComponent = Hero->GetCharacterMovement();
	
}




void UYggHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaTime) 
{
	Super::NativeThreadSafeUpdateAnimation(DeltaTime);
	if (CharacterMovementComponent == nullptr)
	{
		return;
	}
	GroundSpeed = UKismetMathLibrary::VSizeXY(CharacterMovementComponent->Velocity);
	Direction = CalculateDirection(CharacterMovementComponent->Velocity, Hero->GetActorRotation());

}
