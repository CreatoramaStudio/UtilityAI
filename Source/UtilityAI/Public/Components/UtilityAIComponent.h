// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/UtilityAction.h"
#include "UtilityAIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectAction, UUtilityAction*, Value);

UCLASS( ClassGroup=(UtilityAI), meta=(BlueprintSpawnableComponent) )
class UTILITYAI_API UUtilityAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Utility AI")
		TArray<TSubclassOf<UUtilityAction>> ActionTypes;

	UPROPERTY(BlueprintReadOnly, Category = "Utility AI")
		TArray<UUtilityAction*> Actions;

	UPROPERTY(BlueprintReadOnly, Category = "Utility AI")
		UUtilityAction* CurrentAction;

	UPROPERTY(BlueprintAssignable, Category = "Utility AI")
		FOnSelectAction OnSelectAction;

protected:

	UPROPERTY()
		AAIController* AIController;

	bool bSelectingAction;

private:

public:
	// Sets default values for this component's properties
	UUtilityAIComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		bool IsSelectingAction();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		virtual void SelectBestAction();

protected:

	virtual void CreateActions();

	virtual float ScoreAction(UUtilityAction* Action);

private:


};
