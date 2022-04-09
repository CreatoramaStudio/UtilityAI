// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UtilityConsideration.generated.h"

class UUtilityAIComponent;
class AAIController;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class UTILITYAI_API UUtilityConsideration : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame,EditAnywhere, Category = "Utility AI")
	FRuntimeFloatCurve ResponseCurve;

protected:

	UPROPERTY(SaveGame)
	TObjectPtr<UUtilityAIComponent> UtilityAIComponent;

	UPROPERTY(SaveGame)
	TObjectPtr<AAIController> AIController;
	
	UPROPERTY(SaveGame)
	float Score;

private:

public:

	UUtilityConsideration();

	virtual UWorld* GetWorld() const override;

	void InitializeVariables(TObjectPtr<UUtilityAIComponent> InUtilityAIComponent, TObjectPtr<AAIController> InAIController);

	UFUNCTION(BlueprintPure, Category = "Utility AI")
	float GetScore() const;

	UFUNCTION(BlueprintNativeEvent)
	void Construct();


	float EvaluateScore();

protected:

	UFUNCTION(BlueprintPure, Category = "Utility AI")
	UUtilityAIComponent* GetUtilityAIComponent() const;

	UFUNCTION(BlueprintPure, Category = "Utility AI")
	AAIController* GetAIController() const;

	UFUNCTION(BlueprintPure, Category = "Utility AI")
	APawn* GetPawn() const;

	UFUNCTION(BlueprintNativeEvent, Category = "Utility AI")
	float ScoreConsideration();

private:
};
