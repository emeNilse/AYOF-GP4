// Fill out your copyright notice in the Description page of Project Settings.


#include "RecipeEvaluationComponent.h"
#include "ItemDataStruct.h"

// Sets default values for this component's properties
URecipeEvaluationComponent::URecipeEvaluationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void URecipeEvaluationComponent::EvaluateDish_Implementation(FName itemID)
{
	if (!FinalRecipeData) return;

	if (itemID == FinalRecipeID)
	{
		UE_LOG(LogTemp, Display, TEXT("Found a match for the final recipe"));
		OnItemEvaluated.Broadcast(1);
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("NO MATCH for final recipe"));
	
	OnItemEvaluated.Broadcast(0);
}

// Called when the game starts
void URecipeEvaluationComponent::BeginPlay()
{
	Super::BeginPlay();

	// save the data about the final dish 
	if (!IngredientsTable) return;
	FString contextString = FString(IngredientsTable->GetFName().ToString() + " trying to find row named " + FinalRecipeID.ToString());
	FinalRecipeData = IngredientsTable->FindRow<FItemDataStruct>(FinalRecipeID, contextString);
	
}


// Called every frame
void URecipeEvaluationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

