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

	UPROPERTY(BlueprintReadOnly, Category = "Utility AI")
		TArray<UUtilityAction*> Actions;

	UPROPERTY(BlueprintReadOnly, Category = "Utility AI")
		UUtilityAction* CurrentAction;

	UPROPERTY(BlueprintAssignable, Category = "Utility AI")
		FOnSelectAction OnSelectAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
		bool bRandomActionIfSelectBestActionFails = true;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Utility AI")
		TSet<TSubclassOf<UUtilityAction>> DefaultActionTypes;

	UPROPERTY(EditAnywhere, Category = "Utility AI")
		bool bSelectBestActionOnTick = true;

	UPROPERTY()
		AAIController* AIController;

	bool bSelectingAction;

private:

public:
	// Sets default values for this component's properties
	UUtilityAIComponent();

	virtual void OnRegister() override;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		void SetSelectBestActionOnTick(bool Value);

	UFUNCTION(BlueprintPure, Category = "Utility AI")
		bool GetSelectBestActionOnTick();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		bool IsSelectingAction();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		virtual bool SelectBestAction();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		void AddAction(TSubclassOf<UUtilityAction> ActionType);

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		bool RemoveAction(TSubclassOf<UUtilityAction> ActionType);


protected:

	virtual void CreateDefaultActions();

	virtual float ScoreAction(UUtilityAction* Action);

private:


};
