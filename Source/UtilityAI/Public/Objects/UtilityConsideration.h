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

	UPROPERTY()
		UUtilityAIComponent* UtilityAIComponent;

	UPROPERTY()
		AAIController* AIController;

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
