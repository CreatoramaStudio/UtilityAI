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
	
	CreateActions();

	SelectBestAction();
}

void UUtilityAIComponent::OnRegister()
{
	Super::OnRegister();

	if (GetOwner())
	{
		AIController = Cast<AAIController>(GetOwner());
	}
}

bool UUtilityAIComponent::IsSelectingAction()
{
	return bSelectingAction;
}

void UUtilityAIComponent::CreateActions()
{
	Actions.Empty();

	for (auto ActionType : ActionTypes)
	{
		if (ActionType)
		{
			UUtilityAction* Action = NewObject<UUtilityAction>(AIController, ActionType);
			Actions.Add(Action);
			Action->InitializeVariables(this, AIController);
			Action->CreateConsiderations();
			Action->Construct();
		}
	}
}

void UUtilityAIComponent::SelectBestAction()
{
	bSelectingAction = true;

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

	CurrentAction = BestAction;

	bSelectingAction = false;

	if (OnSelectAction.IsBound())
	{
		OnSelectAction.Broadcast(CurrentAction);
	}

	if (CurrentAction)
	{
		CurrentAction->ExecuteAction();
	}
}

float UUtilityAIComponent::ScoreAction(UUtilityAction* Action)
{
	float Score = 1;

	if (Action->Considerations.Num() <= 0)
	{
		return Action->GetScore();
	}

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

