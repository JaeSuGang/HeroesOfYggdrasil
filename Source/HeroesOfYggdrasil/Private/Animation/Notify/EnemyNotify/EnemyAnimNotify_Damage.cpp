// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/EnemyNotify/EnemyAnimNotify_Damage.h"
#include "Enemy/Interface/AttackInterface.h"

void UEnemyAnimNotify_Damage::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin( MeshComp, Animation, TotalDuration, EventReference);

	IAttackInterface* Interface = Cast<IAttackInterface>(MeshComp->GetOwner());
	Interface->AttackStart();
}

void UEnemyAnimNotify_Damage::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UEnemyAnimNotify_Damage::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	IAttackInterface* Interface = Cast<IAttackInterface>(MeshComp->GetOwner());
	// MeshComp->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName, true);
	Interface->AttackEnd();
}
