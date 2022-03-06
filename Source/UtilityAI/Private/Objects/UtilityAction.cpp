// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/UtilityAction.h"
#include "Objects/UtilityConsideration.h"
#include "Components/UtilityAIComponent.h"
#include "AIController.h"

UUtilityAction::UUtilityAction()
{

}

UWorld* UUtilityAction::GetWorld() const
{
	if(!AIController)
	{
		return nullptr;
	}

	return AIController->GetWorld();
}

void UUtilityAction::InitializeVariables(UUtilityAIComponent* InUtilityAIComponent, AAIController* InAIController)
{
	UtilityAIComponent = InUtilityAIComponent;
	AIController = InAIController;

	if (AIController->GetPawn())
	{
		Pawn = AIController->GetPawn();
	}
}

void UUtilityAction::CreateConsiderations()
{
	Considerations.Empty();

	for (auto ConsiderationType : ConsiderationTypes)
	{
		if (ConsiderationType)
		{
			UUtilityConsideration* Consideration = NewObject<UUtilityConsideration>(UtilityAIComponent, ConsiderationType);
			Considerations.Add(Consideration);
			Consideration->InitializeVariables(UtilityAIComponent, AIController);
			Consideration->Construct();
		}
	}
}

void UUtilityAction::SetScore(float Value)
{
	Score = FMath::Clamp(Value, 0.f, 1.f);
}

bool UUtilityAction::IsExecutingAction()
{
	return bExecutingAction;
}

float UUtilityAction::GetScore()
{
	return Score;
}

void UUtilityAction::Construct_Implementation()
{
	return;
}

void UUtilityAction::ExecuteAction()
{
	bExecutingAction = true;
	EnterAction();
}

void UUtilityAction::FinishAction()
{
	ExitAction(false);

	bExecutingAction = false;

	if (UtilityAIComponent)
	{
		UtilityAIComponent->SelectBestAction();
	}
}

void UUtilityAction::CancelAction()
{
	ExitAction(true);

	bExecutingAction = false;

	if (UtilityAIComponent)
	{
		UtilityAIComponent->SelectBestAction();
	}
}

void UUtilityAction::EnterAction_Implementation()
{

}

void UUtilityAction::ExitAction_Implementation(bool bCanceled)
{
}



