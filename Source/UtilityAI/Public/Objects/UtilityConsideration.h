// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Utility AI")
	FGameplayTag ConsiderationTag;

	UPROPERTY(EditAnywhere, Category = "Utility AI")
	FRuntimeFloatCurve ResponseCurve;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Utility AI")
		UUtilityAIComponent* UtilityAIComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Utility AI")
		AAIController* AIController;

	UPROPERTY(BlueprintReadOnly, Category = "Utility AI")
		APawn* Pawn;

	float Score;

private:

public:

	UUtilityConsideration();

	virtual UWorld* GetWorld() const override;

	void InitializeVariables(UUtilityAIComponent* InUtilityAIComponent, AAIController* InAIController);

	UFUNCTION(BlueprintPure, Category = "Utility AI")
		float GetScore();

	UFUNCTION(BlueprintNativeEvent)
		void Construct();


	float EvaluateScore();

protected:

	UFUNCTION(BlueprintNativeEvent)
		float ScoreConsideration();

private:
	
};
