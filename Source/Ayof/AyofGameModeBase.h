// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AyofGameModeBase.generated.h"

class UDialogueManagerComponent;

USTRUCT(BlueprintType)
struct FGamepadIconLookup : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Type1Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Type2Icon;

};

UENUM()
enum class ESeason : uint8
{
	Spring UMETA(DisplayName = "Spring"),
	Summer UMETA(DisplayName = "Summer"),
	Autumn UMETA(DisplayName = "Autumn"),
	Winter UMETA(DisplayName = "Winter")
};
/**
 * 
 */
UCLASS(Blueprintable)
class AYOF_API AAyofGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAyofGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Dialogue)
	TObjectPtr < UDialogueManagerComponent> DialogueManager;

	

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category=Seasons)
	ESeason CurrentSeason;

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Seasons)
	ESeason NextSeason;

	UPROPERTY(EditAnywhere, NoClear, BlueprintReadOnly, Category = Seasons)
	FName NextLevelOverride;

	UPROPERTY(BlueprintReadWrite, Category = Levels)
	bool LoadNextLevelTriggered;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Seasons)
	void StartSeason();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Seasons)
	void EndSeason();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Seasons)
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = Seasons)
	void OpenLevelBySeasonEnum();

	UFUNCTION(BlueprintCallable, Category = Seasons)
	void LoadNextSeason(bool useNextLevelOverride = false);
};
