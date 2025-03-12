// Coded By AssortRock Unreal Engine Class Project


#include "Component/ActorComponent/TimeEventComponent.h"

// Sets default values for this component's properties
UTimeEventComponent::UTimeEventComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTimeEventComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTimeEventComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


    // 이벤트가 비어 있으면 바로 리턴
    if (Events.IsEmpty())
    {
        return;
    }

    // 뒤에서부터 순회하여 이벤트 처리 (배열 크기 변경에 안전)
    for (int32 i = Events.Num() - 1; i >= 0; --i)
    {
        FTimeEvent& Event = Events[i];

        // 시작 타이머를 DeltaTime만큼 감소
        Event.StartTimer -= DeltaTime;

        // 시작 타이머가 0 이하일 때만 시작 함수 실행
        if (Event.StartTimer <= 0.0f && !Event.bIsStarted)
        {
            if (Event.StartFunction)
            {
                Event.StartFunction();
            }
            Event.bIsStarted = true;
        }

        // 현재 시간 업데이트
        Event.CurTime += DeltaTime;

        // 업데이트 함수가 있다면 호출
        if (Event.UpdateFunction)
        {
            Event.UpdateFunction(DeltaTime, Event.CurTime); // 업데이트 함수 호출

            // 루프 타이머를 초과한 경우 종료 함수 호출
            if (Event.LoopTimer < Event.CurTime)
            {
                if (Event.EndFunction)
                {
                    Event.EndFunction(); // 종료 함수 호출
                }

                // 루프가 아닌 이벤트는 삭제
                if (!Event.bIsLoop)
                {
                    Events.RemoveAt(i); // 이벤트 삭제
                }
                else
                {
                    // 루프 이벤트는 초기화
                    Event.StartTimer = 0.0f;
                    Event.CurTime = 0.0f;
                    Event.bIsStarted = false;
                }
            }
        }
    }
	// ...


}
void UTimeEventComponent::AddEvent(float StartTimer, float LoopTimer, TFunction<void(float, float)> UpdateFunction, bool IsLoop, TFunction<void()> StartFunction, TFunction<void()> EndFunction)
{
    FTimeEvent& Event = Events.Emplace_GetRef();
    Event.StartTimer = StartTimer;
    Event.LoopTimer = LoopTimer;
    Event.UpdateFunction = UpdateFunction;
    Event.bIsLoop = IsLoop;
    Event.StartFunction = StartFunction;
    Event.EndFunction = EndFunction;
}
