// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ItemDataStruct.h"
#include "CookingStation.generated.h"


UCLASS()
class AYOF_API ACookingStation : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACookingStation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (ToolTip = "used to indicate if container ui is onscreen."))
	bool bIsContainerUiVisible{ false };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CookingStation", meta = (ToolTip = "If True minigame will only play when valid ingredients added. if false minigame will take any ingredients."))
	bool bMatchToMinigame{ true };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CookingStation", meta = (
		ToolTip = "If True minigame will try to match ingredients to recipes."))
	bool bUseRecipes{ true };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CookingStation", meta = (
		EditCondition = "bUseRecipes",
		ToolTip = "If True minigame will try to match ingredients to recipes."))
	UDataTable* RecipeDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CookingStation", meta = (
		EditCondition = "bUseRecipes",
		ToolTip = "the item data struct for template data about the recipe's output item."))
	FItemDataStruct RecipeResultData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueReactions", meta = (InlineEditConditionToggle))
	bool bShowDialogueOnPossess{ false };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueReactions", meta = (
		EditCondition = "bShowDialogueOnPossess",
		ToolTip = "row name in player feedback dialogue table for when the player possesses this station"))
	FName PossessedDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueReactions", meta = (InlineEditConditionToggle))
	bool bShowDialogueOnUnPossess{ false };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueReactions", meta = (
		EditCondition = "bShowDialogueOnUnPossess",
		ToolTip = "row name in player feedback dialogue table for when the player leaves this station"))
	FName UnPossessedDialogue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueReactions", meta = (
		ToolTip = "row name in player feedback dialogue table for when no ingredients submitted and mingame started"))
	FName NoIngredients;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueReactions", meta = (
		ToolTip = "row name in player feedback dialogue table for when any invalid item submitted and mingame started"))
	FName InvalidIngredient;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueReactions" )
	bool bShowDialogueOnMinigameResult{ false };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueReactions", meta = (
		EditCondition = "bShowDialogueOnMinigameResult", EditConditionHides,
		ToolTip = "row name in player feedback dialogue table for when minigame returns a cooking success"))
	FName SuccessfulCooking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DialogueReactions", meta = (
		EditCondition = "bShowDialogueOnMinigameResult", EditConditionHides,
		ToolTip = "row name in player feedback dialogue table for when minigame returns a cooking failure"))
	FName FailedCooking;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
