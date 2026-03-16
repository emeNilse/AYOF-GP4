// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStruct.h"
#include "DialogueDataStruct.generated.h"

USTRUCT(BlueprintType)
struct FDialogueChoiceData
{
	GENERATED_USTRUCT_BODY()
public:
	FDialogueChoiceData()
		: bIsMiniGameChoice(false)
		, Minigame(EValidMinigame::Stirring)
		, GenericChoiceInt(0)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ChoiceText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Is choosing a minigame"))
	bool bIsMiniGameChoice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "bIsMiniGameChoice", EditConditionHides))
	EValidMinigame Minigame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "!bIsMiniGameChoice", EditConditionHides))
	uint8 GenericChoiceInt;

	// for a conversational dialogue system add database and rowid tag for  if it redirects to a next dialogue
};



/**
 * 
 */
USTRUCT(BlueprintType)
struct FDialogueDataStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FDialogueDataStruct()
		: Name("NULL")
		, bCanRepeat(false)
		, bHasChoices(false)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Data")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Data")
	bool bCanRepeat;

	// for a conversational dialogue system add database and rowid tag for  if this dialogue queues another one to play immediately

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Data")
	FText DisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choice Data")
	bool bHasChoices;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Choice Data", meta = (EditCondition = "bHasChoices", EditConditionHides))
	TArray<FDialogueChoiceData> Choices;
};
