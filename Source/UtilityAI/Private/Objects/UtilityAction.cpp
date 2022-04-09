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

void UUtilityAction::InitializeVariables(TObjectPtr<UUtilityAIComponent> InUtilityAIComponent, TObjectPtr<AAIController> InAIController)
{
	UtilityAIComponent = InUtilityAIComponent;
	AIController = InAIController;
}

void UUtilityAction::CreateConsiderations()
{
	Considerations.Empty();

	for (const auto& ConsiderationType : ConsiderationTypes)
	{
		if (ConsiderationType)
		{
			TObjectPtr<UUtilityConsideration> Consideration = NewObject<UUtilityConsideration>(UtilityAIComponent, ConsiderationType);
			Considerations.Add(Consideration);
			Consideration->InitializeVariables(UtilityAIComponent, AIController);
			Consideration->Construct();
		}
	}
}

void UUtilityAction::SetScore(const float Value)
{
	Score = FMath::Clamp(Value, 0.f, 1.f);
}

bool UUtilityAction::IsExecutingAction() const
{
	return bExecutingAction;
}

float UUtilityAction::GetScore() const
{
	return Score;
}

void UUtilityAction::Construct_Implementation()
{
}

void UUtilityAction::ExecuteAction()
{
	bExecutingAction = true;
	StartAction();
}

void UUtilityAction::FinishAction()
{
	if (bExecutingAction)
	{
		StopAction(false);

		bExecutingAction = false;

		if (UtilityAIComponent)
		{
			UtilityAIComponent->SelectBestAction();
		}
	}
}

void UUtilityAction::CancelAction()
{
	if (bExecutingAction && CanCancelAction())
	{
		StopAction(true);

		bExecutingAction = false;

		if (UtilityAIComponent)
		{
			UtilityAIComponent->SelectBestAction();
		}
	}
}

UUtilityAIComponent* UUtilityAction::GetUtilityAIComponent() const
{
	return UtilityAIComponent;
}

AAIController* UUtilityAction::GetAIController() const
{
	return AIController;
}

APawn* UUtilityAction::GetPawn() const
{
	return AIController->GetPawn();
}

bool UUtilityAction::CanCancelAction_Implementation()
{
	return true;
}

void UUtilityAction::StartAction_Implementation()
{
}

void UUtilityAction::StopAction_Implementation(bool bCanceled)
{
}



