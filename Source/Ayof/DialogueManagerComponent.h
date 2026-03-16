// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueDataStruct.h"
#include "DialogueManagerComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AYOF_API UDialogueManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueManagerComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* CentralDialogueWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WordsPerMinute{ 250 };

	UPROPERTY( BlueprintReadWrite)
	bool CurrentDialogueWaitsForInput;

	UPROPERTY( BlueprintReadWrite)
	bool IsPlayingDialogue;

	float Timer{ 0 };
	bool TimerRunning{ false };

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void StopDisplayTimer() { TimerRunning = false; }

	UFUNCTION(BlueprintCallable)
	void SetDisplayTimer(float seconds);

	UFUNCTION(BlueprintCallable)
	void SetDisplayTimerByText(FText Text, float speedMultiplier);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (ForceAsFunction))
	void RemoveDialogue();

	UFUNCTION(BlueprintCallable)
	float GetDialogueAnimationDuration(FString text, float speedMultiplier = 1.0f);


	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsDialoguePlaying() { return TimerRunning || CurrentDialogueWaitsForInput; }
		
};
