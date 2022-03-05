// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "Objects/UtilityConsideration.h"
#include "UtilityAction.generated.h"

class UUtilityAIComponent;
class AAIController;
/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class UTILITYAI_API UUtilityAction : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Utility AI")
		FGameplayTag ActionTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Utility AI")
		TArray<TSubclassOf<UUtilityConsideration>> ConsiderationTypes;

	UPROPERTY(BlueprintReadOnly, Category = "Utility AI")
		TArray<UUtilityConsideration*> Considerations;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Utility AI")
		UUtilityAIComponent* UtilityAIComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Utility AI")
		AAIController* AIController;

	UPROPERTY(BlueprintReadOnly, Category = "Utility AI")
		APawn* Pawn;

	float Score;

	bool bExecutingAction;

private:

public:

	UUtilityAction();

	virtual UWorld* GetWorld() const override;

	void InitializeVariables(UUtilityAIComponent* InUtilityAIComponent, AAIController* InAIController);

	virtual void CreateConsiderations();

	void SetScore(float Value);

	UFUNCTION(BlueprintPure, Category = "Utility AI")
		bool IsExecutingAction();

	UFUNCTION(BlueprintPure, Category = "Utility AI")
		float GetScore();

	UFUNCTION(BlueprintNativeEvent, Category = "Utility AI")
		void Construct();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		void ExecuteAction();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		void FinishAction();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		void CancelAction();
	
protected:

	UFUNCTION(BlueprintNativeEvent, Category = "Utility AI")
		void EnterAction();
	
	UFUNCTION(BlueprintNativeEvent, Category = "Utility AI")
		void ExitAction(bool bCanceled);

private:

};
