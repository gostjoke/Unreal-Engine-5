#include "BTTask_ClearBlackboardValue.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_ClearBlackboardValue::UBTTask_ClearBlackboardValue() 
{
    NodeName = "Clear Blackboard Value";
}

EBTNodeResult::Type UBTTask_ClearBlackboardValue::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    FName KeyName = GetSelectedBlackboardKey();

    OwnerComp.GetBlackboardComponent()->ClearValue(KeyName);

    return EBTNodeResult::Succeeded;
}
