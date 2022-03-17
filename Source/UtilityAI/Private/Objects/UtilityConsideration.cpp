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
}

float UUtilityConsideration::GetScore()
{
	return Score;
}


void UUtilityConsideration::Construct_Implementation()
{
	return;
}

float UUtilityConsideration::EvaluateScore()
{
	Score = ResponseCurve.GetRichCurve()->Eval(FMath::Clamp(ScoreConsideration(),0.f,1.f));
	return Score;
}

UUtilityAIComponent* UUtilityConsideration::GetUtilityAIComponent() const
{
	return UtilityAIComponent;
}

AAIController* UUtilityConsideration::GetAIController() const
{
	return AIController;
}

APawn* UUtilityConsideration::GetPawn() const
{
	return AIController->GetPawn();
}

float UUtilityConsideration::ScoreConsideration_Implementation()
{
	return 0.0f;
}