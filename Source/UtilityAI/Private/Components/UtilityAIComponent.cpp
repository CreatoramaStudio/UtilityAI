// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UtilityAIComponent.h"
#include "AIController.h"

// Sets default values for this component's properties
UUtilityAIComponent::UUtilityAIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.

	PrimaryComponentTick.bCanEverTick = true;

}


void UUtilityAIComponent::OnRegister()
{
	Super::OnRegister();

	if (GetOwner())
	{
		AIController = Cast<AAIController>(GetOwner());
	}
}

// Called when the game starts
void UUtilityAIComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CreateDefaultActions();

	SetSelectBestActionUpdateType(SelectBestActionUpdateType);
}

void UUtilityAIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (SelectBestActionUpdateType == EUtilityUpdate::Tick)
	{
		SelectBestAction();
	}
}

TArray<UUtilityAction*> UUtilityAIComponent::GetActions() const
{
	return Actions;
}

UUtilityAction* UUtilityAIComponent::GetCurrentAction() const
{
	return CurrentAction;
}

void UUtilityAIComponent::SetSelectBestActionUpdateType(EUtilityUpdate Value, float TimerRate)
{
	SelectBestActionUpdateType = Value;
	SelectBestActionTimerRate = TimerRate;

	switch (SelectBestActionUpdateType)
	{
	case EUtilityUpdate::None:

		SetComponentTickEnabled(false);

		if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}

		SelectBestAction();

		break;
	case EUtilityUpdate::Tick:

		if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		}

		SetComponentTickEnabled(true);
		
		break;
	case EUtilityUpdate::Timer:

		SetComponentTickEnabled(false);

		if (!GetWorld()->GetTimerManager().IsTimerActive(TimerHandle))
		{
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UUtilityAIComponent::SelectBestAction, SelectBestActionTimerRate, true,0);
		}

		break;
	default:
		break;
	}

}

EUtilityUpdate UUtilityAIComponent::GetSelectBestActionUpdateType()
{
	return SelectBestActionUpdateType;
}


bool UUtilityAIComponent::IsSelectingAction()
{
	return bSelectingAction;
}

void UUtilityAIComponent::CreateDefaultActions()
{
	Actions.Empty();

	for (auto ActionType : DefaultActionTypes)
	{
		AddAction(ActionType);
	}
}

void UUtilityAIComponent::SelectBestAction()
{
	bSelectingAction = true;

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

	if (CurrentAction && CurrentAction != BestAction && CurrentAction->IsExecutingAction())
	{
		if (CurrentAction->CanCancelAction())
		{
			CurrentAction->CancelAction();
		}
		else
		{
			bSelectingAction = false;
			return;
		}
		
	}

	if (BestAction)
	{
		CurrentAction = BestAction;
		bSelectingAction = false;
	}
	else if(bRandomActionIfSelectBestActionFails)
	{
		CurrentAction = Actions[FMath::RandRange(0, Actions.Num() - 1)];
		bSelectingAction = false;
	}
	else
	{
		bSelectingAction = false;
		return;
	}
	
	

	if (OnSelectAction.IsBound())
	{
		OnSelectAction.Broadcast(CurrentAction);
	}

	if (CurrentAction)
	{
		CurrentAction->ExecuteAction();
	}

	return;
}

bool UUtilityAIComponent::AddAction(TSubclassOf<UUtilityAction> ActionType)
{
	if (ActionType)
	{
		for (auto Action : Actions)
		{
			if (Action->GetClass() == ActionType)
			{
				return false;
			}
		}

		UUtilityAction* Action = NewObject<UUtilityAction>(AIController, ActionType);
		Actions.Add(Action);
		Action->InitializeVariables(this, AIController);
		Action->CreateConsiderations();
		Action->Construct();

		return true;
	}

	return false;
}

bool UUtilityAIComponent::RemoveAction(TSubclassOf<UUtilityAction> ActionType)
{
	if (CurrentAction && CurrentAction->GetClass() == ActionType)
	{
		Actions.Remove(CurrentAction);

		SelectBestAction();

		return true;
	}

	for (auto Action : Actions)
	{
		if (Action->GetClass() == ActionType)
		{
			Actions.Remove(Action);
			return true;
		}
	}

	return false;
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

