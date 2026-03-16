// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceDialogueSubsystem.h"
#include "Engine/DataTable.h"
#include "DialogueDataStruct.h"

void UGameInstanceDialogueSubsystem::AddDialogueEvent(FName rowKey, EDialogueType dialogueType)
{
	UE_LOG(LogTemp, Warning, TEXT("Game Instance Subsystem for Dialogue is Deprecated. Use Dialogue Event Components instead"));
	//FDialogueDataStruct* dataRow;
	/*switch (dialogueType)
	{
	case EDialogueType::Seasons:
		GetSeasonDialogue(rowKey);
		break;
	case EDialogueType::Choices:
		break;
	case EDialogueType::Items:
		break;
	case EDialogueType::UserFeedback:
		break;
	default:
		break;
	}*/
}



void UGameInstanceDialogueSubsystem::GetSeasonDialogue(FName seasonKey)
{
	TArray<FDialogueDataStruct*> rows;
	bool bDialogueShown = false;
	SeasonsDialogueTable->GetAllRows<FDialogueDataStruct>(FString("Seasons Dialogue Table add dialogue event"), rows);

	for (FDialogueDataStruct* row : rows)
	{
		if (row->Name == seasonKey)
		{
			// do something to select which match to use, for now use first match
			bDialogueShown = TryShowDialogue(row);
		}
	}

	if(!bDialogueShown) UE_LOG(LogTemp, Warning, TEXT("Tried to show Dialogue but none found to show"));
}

bool UGameInstanceDialogueSubsystem::TryShowDialogue(FDialogueDataStruct* dialogueData)
{
	if (!dialogueData) return false; // error msging on null row returned handled by context string sent to row search

	// actually do some logic to determine if this should be sent to ui or not first 
	// but for now go straight to testing

	SendTextToUI(dialogueData);
	return true;
}

void UGameInstanceDialogueSubsystem::SendTextToUI(FDialogueDataStruct* dialogueData)
{
	UE_LOG(LogTemp, Warning, TEXT("Found row with text: %s"), *dialogueData->DisplayText.ToString());
}
