// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueManagerComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/UserWidget.h"


// Sets default values for this component's properties
UDialogueManagerComponent::UDialogueManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UDialogueManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UDialogueManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TimerRunning && !CurrentDialogueWaitsForInput)
	{
		Timer -= DeltaTime;
		if (Timer <= 0.0f)
		{
			RemoveDialogue();
			TimerRunning = false;
		}
	}
	// ...
}

void UDialogueManagerComponent::SetDisplayTimer(float seconds)
{
	TimerRunning = true;
	CurrentDialogueWaitsForInput = false;
	Timer = seconds;
}

void UDialogueManagerComponent::SetDisplayTimerByText(FText Text, float speedMultiplier)
{
	TimerRunning = true;
	CurrentDialogueWaitsForInput = false;
	Timer = GetDialogueAnimationDuration(Text.ToString(), speedMultiplier);
}

void UDialogueManagerComponent::RemoveDialogue_Implementation()
{
	CentralDialogueWidget->RemoveFromViewport();
	CurrentDialogueWaitsForInput = false;
	TimerRunning = false;
	UE_LOG(LogTemp, Display, TEXT("Dialogue Manager removed the dialogue widget from viewport"));
}

float UDialogueManagerComponent::GetDialogueAnimationDuration(FString text, float speedMultiplier)
{
	//from my reading most word per minute calculations define a word as 5 characters including white space
	float lengthOfWord{ 5.0f };

	// return the larger of 1 second or the calculated reading speed time
	return FMath::Max( 1.0f, (text.Len() / (lengthOfWord * WordsPerMinute)) * 60.0f);
}

