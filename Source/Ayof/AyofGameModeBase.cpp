// Fill out your copyright notice in the Description page of Project Settings.


#include "AyofGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "DialogueManagerComponent.h"

void AAyofGameModeBase::StartSeason_Implementation()
{}

void AAyofGameModeBase::EndSeason_Implementation()
{}

AAyofGameModeBase::AAyofGameModeBase()
{
	DialogueManager = CreateDefaultSubobject<UDialogueManagerComponent>(TEXT("Dialogue Manager Component"));
}

void AAyofGameModeBase::EndGame_Implementation()
{}

void AAyofGameModeBase::OpenLevelBySeasonEnum()
{
	FText SeasonEnumValueText = UEnum::GetDisplayValueAsText(NextSeason);
	
	const UEnum* EnumPtr = StaticEnum<ESeason>();
	if (!EnumPtr) return;
	
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *(EnumPtr->GetDisplayNameTextByValue((int64)NextSeason).ToString()));
	UGameplayStatics::OpenLevel(GetWorld(), *(EnumPtr->GetDisplayNameTextByValue((int64)NextSeason).ToString()));
}


void AAyofGameModeBase::LoadNextSeason(bool useNextLevelOverride)
{
	if (useNextLevelOverride)
	{
		UGameplayStatics::OpenLevel(GetWorld(), NextLevelOverride);
	}
	else
	{
		OpenLevelBySeasonEnum();
	}
}
