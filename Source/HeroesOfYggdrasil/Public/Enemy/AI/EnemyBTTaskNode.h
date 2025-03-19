// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Data/YggEnumData.h"
#include "Data/YggStructData.h"
#include "Enemy/EnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UEnemyBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UEnemyBTTaskNode();

	virtual void Start(UBehaviorTreeComponent& _OwnerComp);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory) override;

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

	void ChangeState(UBehaviorTreeComponent& _OwnerComp, EEnemyAIState _State);

	FPlayAIData& GetPlayAIData(UBehaviorTreeComponent& _OwnerComp);

	void TargetCheck(UBehaviorTreeComponent& _OwnerComp);

	void YggdrasilCheck(UBehaviorTreeComponent& _OwnerComp);

protected:
	UPROPERTY(Category = "Enemy", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EEnemyAIState EnemyAIStateValue = EEnemyAIState::TraceYggdrasil;
private:
	UPROPERTY(EditAnywhere, Category = "Target")
	FBlackboardKeySelector InTargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Target")
	float RotationInterSpeed;
	
};
