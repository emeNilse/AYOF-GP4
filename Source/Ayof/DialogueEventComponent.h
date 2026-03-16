// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueDataStruct.h"
#include "DialogueEventComponent.generated.h"

struct FDialogueDataStruct;
struct FDialogueChoiceData;
class UDialogueManagerComponent;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AYOF_API UDialogueEventComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueEventComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr < UDialogueManagerComponent> DialogueManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr < UDataTable> DialogueTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DialogueRowName;

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "If searchByNameField is true searches for key in the every row's Name property and tries to display the first match. if searchByNameField is false it searches for the key in the row names. row names should be the more efficient search due to unreal's datatable architecture."))
	void StartDialogueEvent(FName key, bool searchByNameField = false);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (ToolTip = "starts a dialogue event using the name in DialogueRowName, use StartDialogueEvent for customizable behavior"))
	void OnInteract();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DialogueChoiceSelected(uint8 value, const FText& choiceText, bool bIsMinigameChoice);

protected:
	UPROPERTY(BlueprintReadOnly)
	FName UidColumn{ "RowName" };

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void GetDialogueByRowName(FName key, FDialogueDataStruct& outDialogueData);

	FDialogueDataStruct* GetDialogueDataByRow(FName key);

	//UFUNCTION(BlueprintCallable)
	FDialogueDataStruct* GetDialogueDataByNameProperty(FName key);
	

	bool TryShowDialogue(FDialogueDataStruct* dialogueData); 

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Meta = (ForceAsFunction))
	void SendTextToUI(const FDialogueDataStruct& dialogueData);//const FName& name, const bool canRepeat, const FText& text, const bool hasChoices, const TArray<FDialogueChoiceData>& choices);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
