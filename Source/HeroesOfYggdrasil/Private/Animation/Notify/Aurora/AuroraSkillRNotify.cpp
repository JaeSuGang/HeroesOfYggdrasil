// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Aurora/AuroraSkillRNotify.h"
#include "Enemy/EnemyCharacter.h"

void UAuroraSkillRNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner())) return;


}