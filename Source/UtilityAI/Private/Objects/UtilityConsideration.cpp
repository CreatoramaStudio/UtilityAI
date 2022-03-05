// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/UtilityConsideration.h"
#include "Components/UtilityAIComponent.h"
#include "AIController.h"

UUtilityConsideration::UUtilityConsideration()
{
	ResponseCurve.GetRichCurve()->AddKey(0, 0, true);
	ResponseCurve.GetRichCurve()->AddKey(1, 1,true);
}

UWorld* UUtilityConsideration::GetWorld() const
{
	if (!AIController)
	{
		return nullptr;
	}

	return AIController->GetWorld();
}

void UUtilityConsideration::InitializeVariables(UUtilityAIComponent* InUtilityAIComponent, AAIController* InAIController)
{
	UtilityAIComponent = InUtilityAIComponent;
	AIController = InAIController;

	if (AIController->GetPawn())
	{
		Pawn = AIController->GetPawn();
	}
}

float UUtilityConsideration::GetScore()
{
	return Score;
}


void UUtilityConsideration::Construct_Implementation()
{
}

float UUtilityConsideration::EvaluateScore()
{
	Score = ResponseCurve.GetRichCurve()->Eval(FMath::Clamp(ScoreConsideration(),0.f,1.f));
	return Score;
}

float UUtilityConsideration::ScoreConsideration_Implementation()
{
	return 0.0f;
}