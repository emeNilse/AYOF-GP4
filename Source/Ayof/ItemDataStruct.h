#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStruct.generated.h"

UENUM(BlueprintType)
enum class EItemQuality : uint8
{
	Unprepared UMETA(DisplayName = "Unprepared"),
	Prepared UMETA(DisplayName = "Prepared")
};

UENUM(BlueprintType)
enum class EItemGrade : uint8
{
	NoGrade,
	Botched,
	Acceptable,
	Eggselent
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Ingredient UMETA(DisplayName = "Ingredient"),
	Dish UMETA(DisplayName = "Dish")
};

UENUM(BlueprintType)
enum class EValidMinigame : uint8
{
	Stirring UMETA(DisplayName = "Stirring"),
	Kneading UMETA(DisplayName = "Kneading"),
	Assembling UMETA(DisplayName = "Assembling"),
	Oven UMETA(DisplayName = "Oven"),
	Chopping UMETA(DisplayName = "Chopping"),
	Cracking UMETA(DisplayName = "Cracking"),
	None UMETA(DisplayName = "None")
};

USTRUCT(BlueprintType)
struct FItemTextData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText InteractText;
};

USTRUCT(BlueprintType)
struct FItemAssetData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;
};

USTRUCT(BlueprintType)
struct FItemNumericData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStackable;
};

USTRUCT(BlueprintType)
struct FItemDataStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Item Data", BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditAnywhere, Category = "Item Data", BlueprintReadWrite)
	EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "Item Data", BlueprintReadWrite)
	EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "Item Data", BlueprintReadWrite)
	EItemGrade ItemGrade;

	UPROPERTY(EditAnywhere, Category = "Item Data", BlueprintReadWrite)
	EValidMinigame ValidMinigame;

	UPROPERTY(EditAnywhere, Category = "Item Data", BlueprintReadWrite)
	FItemAssetData ItemAssetData;

	UPROPERTY(EditAnywhere, Category = "Item Data", BlueprintReadWrite)
	FItemNumericData ItemNumericData;

	UPROPERTY(EditAnywhere, Category = "Item Data", BlueprintReadWrite)
	FItemTextData ItemTextData;
};

