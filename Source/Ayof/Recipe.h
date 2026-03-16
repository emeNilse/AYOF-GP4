// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemDataStruct.h"
#include "Recipe.generated.h"

USTRUCT(BlueprintType)
struct FRecipe
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FItemDataStruct> Ingredients;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FItemDataStruct Result;
};


