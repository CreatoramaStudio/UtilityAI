// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UtilityAIComponent.h"
#include "AIController.h"

// Sets default values for this component's properties
UUtilityAIComponent::UUtilityAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	//PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UUtilityAIComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		AIController = Cast<AAIController>(GetOwner());
	}
	
	CreateActions();

	CalculateBestAction();
}

bool UUtilityAIComponent::IsDecidingBestAction()
{
	return !FinishedDeciding;
}

void UUtilityAIComponent::CreateActions()
{
	Actions.Empty();

	for (auto ActionType : ActionTypes)
	{
		if (ActionType)
		{
			UUtilityAction* Action = NewObject<UUtilityAction>(GetOwner(), ActionType);
			Actions.Add(Action);
			Action->InitializeVariables(this, AIController);
			Action->CreateConsiderations();
			Action->Construct();
		}
	}
}

void UUtilityAIComponent::CalculateBestAction()
{
	FinishedDeciding = false;

	if (CurrentAction && CurrentAction->IsExecutingAction())
	{
		CurrentAction->CancelAction();
	}

	float Score = 0;
	UUtilityAction* BestAction = nullptr;

	for (auto Action : Actions)
	{
		if (ScoreAction(Action) > Score)
		{
			BestAction = Action;
			Score = BestAction->GetScore();
		}
	}

	FinishedDeciding = true;

	CurrentAction = BestAction;

	if (CurrentAction)
	{
		CurrentAction->ExecuteAction();
	}
	
}

float UUtilityAIComponent::ScoreAction(UUtilityAction* Action)
{
	float Score = 1;

	for (auto Consideration : Action->Considerations)
	{
		float ConsiderationScore = Consideration->EvaluateScore();
		Score *= ConsiderationScore;
		if (Score == 0)
		{
			Action->SetScore(0);
			return Action->GetScore();
		}
	}

	// Averaging scheme of overall score
	float OriginalScore = Score;
	float ModFactor = 1 - (1 / Action->Considerations.Num());
	float makeupValue = (1 - OriginalScore) * ModFactor;
	Action->SetScore(OriginalScore + (makeupValue * OriginalScore));

	return Action->GetScore();
}

