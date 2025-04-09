// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Hero/SpawnProjetileAnimNotify.h"

#include "Player/YggHero.h"
#include "Global/YggProjectileActor.h"
void USpawnProjetileAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (ProjectileClass)
	{
		AYggHero* Actor = Cast<AYggHero>(MeshComp->GetOwner());
		if (IsValid(Actor))
		{
			FVector SpawnLocation = Actor->GetMesh()->GetSocketLocation(SocketName);
			FRotator SpawnRotation = Actor->GetActorRotation();
			FActorSpawnParameters SpawnParams;
			AYggProjectileActor* Projectile = GetWorld()->SpawnActor<AYggProjectileActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}
}

