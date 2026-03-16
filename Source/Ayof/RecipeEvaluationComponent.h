// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RecipeEvaluationComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FOnItemEvaluated, URecipeEvaluationComponent, OnItemEvaluated, uint8, quality);

struct FItemDataStruct;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AYOF_API URecipeEvaluationComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URecipeEvaluationComponent();

	UPROPERTY(EditAnywhere, meta = (ToolTip = "This is the itemId in the ingredients table that the season is looking for to end the season"))
	FName FinalRecipeID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* IngredientsTable;

	FItemDataStruct* FinalRecipeData;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (ToolTip = "Takes Id to look up row in ingredient database", ForceAsFunction))
	void EvaluateDish(FName itemID);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnItemEvaluated OnItemEvaluated;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
