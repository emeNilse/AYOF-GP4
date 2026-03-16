// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomStructs.h"
#include "RHIResourceReplace.h"
#include "Kismet/GameplayStatics.h"
#include "MathUtil.h"
#include "TaskManager.generated.h"

class AGameContainerState;
class ATaskBase;

UCLASS()
class AYOF_API ATaskManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaskManager();

	//Nils took this out
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Task Manager")
	AGameContainerState* GameContainerState;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void RetrieveTask(ATaskBase* InTask);
	
	UFUNCTION()
	void GetAndProcessAllTasksInLevel();

	UFUNCTION()
	void CheckShipStatusAndExecuteTasks(float InDeltaTime);

private:
	TArray<ATaskBase*> Tasks;
	
	UPROPERTY()
	float TimeBetweenTask;
	UPROPERTY()
	float TaskTimer;
};
