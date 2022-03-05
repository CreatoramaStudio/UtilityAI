// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Objects/UtilityAction.h"
#include "UtilityAIComponent.generated.h"



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

protected:

	UPROPERTY()
		AAIController* AIController;

	bool FinishedDeciding;

private:

public:
	// Sets default values for this component's properties
	UUtilityAIComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
		bool IsDecidingBestAction();

	UFUNCTION(BlueprintCallable, Category = "Utility AI")
	virtual void CalculateBestAction();

protected:

	virtual void CreateActions();

	virtual float ScoreAction(UUtilityAction* Action);

private:


};
