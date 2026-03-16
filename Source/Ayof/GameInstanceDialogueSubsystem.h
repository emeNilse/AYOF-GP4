// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameInstanceDialogueSubsystem.generated.h"

class UDataTable;
struct FDialogueDataStruct;

UENUM()
enum class EDialogueType : uint8
{
	Seasons UMETA(DisplayName = "Seasons Exposition Table"),
	Choices UMETA(DisplayName = "Choice Prompts"),
	Items UMETA(DisplayName = "Item Exposition"),
	UserFeedback UMETA(DisplayName = "User Feedback"),
};

/**
 * 
 */
UCLASS()
class AYOF_API UGameInstanceDialogueSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public: 
	//UGameInstanceDialogueSubsystem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* SeasonsDialogueTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* ChoicesDialogueTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* ItemsDialogueTable;

	UFUNCTION(BlueprintCallable)
	void AddDialogueEvent(FName rowKey, EDialogueType dialogueType);

private:
	void GetSeasonDialogue(FName seasonKey);

	bool TryShowDialogue(FDialogueDataStruct* dialogueData);

	void SendTextToUI(FDialogueDataStruct* dialogueData);
};
