// Fill out your copyright notice in the Description page of Project Settings.

//#include "GameInstanceDialogueSubsystem.h"

#include "DialogueEventComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AyofGameModeBase.h"
#include "DialogueManagerComponent.h"

// Sets default values for this component's properties
UDialogueEventComponent::UDialogueEventComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UDialogueEventComponent::StartDialogueEvent(FName rowKey, bool searchByNameField)
{
	bool bDialogueShown = false;
	FDialogueDataStruct* dialogueData;

	if (searchByNameField)
	{
		dialogueData = GetDialogueDataByNameProperty(rowKey);
	}
	else
	{
		dialogueData = GetDialogueDataByRow(rowKey);
	}

	bDialogueShown = TryShowDialogue(dialogueData);

	//bDialogueShown = TryShowDialogue(*dialogueData);
	if (!bDialogueShown) UE_LOG(LogTemp, Warning, TEXT("Tried to show Dialogue but none found to show"));
}

void UDialogueEventComponent::OnInteract_Implementation()
{
	StartDialogueEvent(DialogueRowName);
}

// Called when the game starts
void UDialogueEventComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AAyofGameModeBase* gameMode = Cast<AAyofGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!gameMode)
	{
		UE_LOG(LogTemp, Error, TEXT("Game Mode not found, cannot add Dialogue Manager"));
		return;
	}

	DialogueManager = gameMode->GetComponentByClass<UDialogueManagerComponent>();
	//UE_LOG(LogTemp, Warning, TEXT("Dialog manager set on %s"), *GetFName().ToString());
}

void UDialogueEventComponent::GetDialogueByRowName(FName key, FDialogueDataStruct& outDialogueData)
{
	//FDataTableRowHandle rowHandle = FDataTableRowHandle();
	FDialogueDataStruct* dialogueData = GetDialogueDataByRow(key);

	if (!dialogueData) return;

	outDialogueData = *dialogueData;
}

FDialogueDataStruct* UDialogueEventComponent::GetDialogueDataByRow(FName key)
{
	FString contextString = FString(DialogueTable->GetFName().ToString() + " trying to find row with " + key.ToString() + " in rowName");
	FDialogueDataStruct* dialogueData = DialogueTable->FindRow<FDialogueDataStruct>(key, contextString);

	if (!dialogueData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find Dialogue with row name %s in table %s"), *key.ToString(), *DialogueTable->GetFName().ToString());
		return nullptr;
	}

	return dialogueData;
}

FDialogueDataStruct* UDialogueEventComponent::GetDialogueDataByNameProperty(FName key)
{
	TArray<FDialogueDataStruct*> rows;
	FString contextString = FString(DialogueTable->GetFName().ToString() + " trying to find row with "+ key.ToString() + " in column Name");
	DialogueTable->GetAllRows<FDialogueDataStruct>(contextString, rows);

	for (FDialogueDataStruct* row : rows)
	{
		if (row->Name == key)
		{
			// might want to do some logic to pick randomly between multiple valid rows? 
			return row;
		}
	}

	return nullptr;
}

//FDataTableRowHandle UDialogueEventComponent::GetDialogueRowByNameData(FName key)
//{
//	TArray<FDialogueDataStruct*> rows;
//	FDialogueDataStruct* dialogueData = nullptr;
//	FString contextString = FString(DialogueTable->GetFName().ToString() + " trying to find row with "+ key.ToString() + " in column Name");
//	DialogueTable->GetAllRows<FDialogueDataStruct>(contextString, rows);
//
//	for (FDialogueDataStruct* row : rows)
//	{
//		if (row->Name == key)
//		{
//			dialogueData = row;
//			return FDataTableRowHandle(DialogueTable, row->)
//			break;
//		}
//	}
//
//	if (!dialogueData) return FDataTableRowHandle();
//}

bool UDialogueEventComponent::TryShowDialogue(FDialogueDataStruct* dialogueData)
{
	if (!dialogueData) return false;

	// actually do some logic to determine if this should be sent to ui or not first 
	// but for now go straight to testing

	SendTextToUI(*dialogueData);// ->Name, dialogueData->bCanRepeat, dialogueData->DisplayText, dialogueData->bHasChoices, dialogueData->Choices);
	return true;
}

void UDialogueEventComponent::SendTextToUI_Implementation(const FDialogueDataStruct& dialogueData)//const FName& name, const bool canRepeat, const FText& text, const bool hasChoices, const TArray<FDialogueChoiceData>& choices)
{
	UE_LOG(LogTemp, Warning, TEXT("Found row with text: %s"), *dialogueData.Name.ToString());
}

// Called every frame
void UDialogueEventComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

