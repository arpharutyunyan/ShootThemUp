// Shoot Them Up Game, All Rights Reserved


#include "AI/STUAIController.h"
#include <AI/STUAICharacter.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "Components/STUAIPerceptionComponent.h"

ASTUAIController::ASTUAIController()
{
	STUAIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUAIPerceptionComponent");
	SetPerceptionComponent(*STUAIPerceptionComponent);

	bWantsPlayerState = true;
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (const auto STUCharacter = Cast<ASTUAICharacter>(InPawn))
	{
		RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
	}
	
}

void ASTUAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//const auto AimActor = GetFocusOnActor();
	SetFocus(GetFocusOnActor());
}

AActor* ASTUAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}