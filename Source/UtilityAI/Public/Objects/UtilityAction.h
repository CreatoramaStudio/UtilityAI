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

	UPROPERTY(SaveGame,EditAnywhere, BlueprintReadOnly, Category = "Utility AI")
	FText Name;

	UPROPERTY(SaveGame,EditAnywhere, BlueprintReadOnly, Category = "Utility AI")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Utility AI")
	TSet<TSubclassOf<UUtilityConsideration>> ConsiderationTypes;

	UPROPERTY(SaveGame,BlueprintReadOnly, Category = "Utility AI")
	TArray<UUtilityConsideration*> Considerations;

protected:

	UPROPERTY()
	UUtilityAIComponent* UtilityAIComponent;

	UPROPERTY()
	AAIController* AIController;

	UPROPERTY(SaveGame)
	float Score;

	UPROPERTY(SaveGame)
	bool bExecutingAction;

private:

public:

	UUtilityAction();

	virtual UWorld* GetWorld() const override;

	void InitializeVariables(UUtilityAIComponent* InUtilityAIComponent, AAIController* InAIController);

	virtual void CreateConsiderations();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
	void SetScore(float Value);

	UFUNCTION(BlueprintPure, Category = "Utility AI")
	bool IsExecutingAction() const;

	UFUNCTION(BlueprintPure, Category = "Utility AI")
	float GetScore() const;

	UFUNCTION(BlueprintNativeEvent, Category = "Utility AI")
	void Construct();

	void ExecuteAction();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
	void FinishAction();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
	void CancelAction();

	UFUNCTION(BlueprintNativeEvent, Category = "Utility AI")
	bool CanCancelAction();

protected:

	UFUNCTION(BlueprintPure, Category = "Utility AI")
	UUtilityAIComponent* GetUtilityAIComponent() const;

	UFUNCTION(BlueprintPure, Category = "Utility AI")
	AAIController* GetAIController() const;

	UFUNCTION(BlueprintPure, Category = "Utility AI")
	APawn* GetPawn() const;


	UFUNCTION(BlueprintNativeEvent, Category = "Utility AI")
	void StartAction();

	UFUNCTION(BlueprintNativeEvent, Category = "Utility AI")
	void StopAction(bool bCanceled);

private:
};
