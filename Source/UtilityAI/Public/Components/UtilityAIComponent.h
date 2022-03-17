// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/UtilityAction.h"
#include "UtilityAIComponent.generated.h"

UENUM(BlueprintType)
enum class EUtilityUpdate : uint8
{
	None,
	Tick,
	Timer,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectAction, UUtilityAction*, Value);

UCLASS( ClassGroup=(UtilityAI), meta=(BlueprintSpawnableComponent) )
class UTILITYAI_API UUtilityAIComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "Utility AI")
		FOnSelectAction OnSelectAction;

protected:

	UPROPERTY()
		TArray<UUtilityAction*> Actions;

	UPROPERTY()
		UUtilityAction* CurrentAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Utility AI")
		TSet<TSubclassOf<UUtilityAction>> DefaultActionTypes;

	UPROPERTY(EditAnywhere, Category = "Utility AI")
		EUtilityUpdate SelectBestActionUpdateType = EUtilityUpdate::Timer;

	UPROPERTY(EditAnywhere, Category = "Utility AI", meta = (EditCondition = "SelectBestActionUpdateType==EUtilityUpdate::Timer", EditConditionHides))
		float SelectBestActionTimerRate = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Utility AI")
		bool bRandomActionIfSelectBestActionFails = true;

	UPROPERTY()
		AAIController* AIController;

	bool bSelectingAction;

	FTimerHandle TimerHandle;

private:

public:
	// Sets default values for this component's properties
	UUtilityAIComponent();

	virtual void OnRegister() override;

	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category = "Utility AI")
	TArray<UUtilityAction*> GetActions() const;

	UFUNCTION(BlueprintPure, Category = "Utility AI")
	UUtilityAction* GetCurrentAction() const;

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		void SetSelectBestActionUpdateType(EUtilityUpdate Value, float TimerRate = .5f);

	UFUNCTION(BlueprintPure, Category = "Utility AI")
		EUtilityUpdate GetSelectBestActionUpdateType();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		bool IsSelectingAction();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		virtual void SelectBestAction();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		bool AddAction(TSubclassOf<UUtilityAction> ActionType);

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		bool RemoveAction(TSubclassOf<UUtilityAction> ActionType);


protected:

	virtual void CreateDefaultActions();

	virtual float ScoreAction(UUtilityAction* Action);

private:


};
