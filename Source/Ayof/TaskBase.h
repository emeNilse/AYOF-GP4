// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomStructs.h"
//#include "NiagaraSystem.h"
//#include "NiagaraComponent.h"
//#include "NiagaraFunctionLibrary.h"
#include "TaskBase.generated.h"

class ATaskManager;

UCLASS()
class AYOF_API ATaskBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATaskBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void SetTaskManager(ATaskManager* InManager);

	UFUNCTION(BlueprintCallable)
	void SendTaskToManager(ETaskStatus InStatus);

	UFUNCTION(BlueprintCallable)
	void SetActive(bool InActiveState);

	UFUNCTION(BluePrintCallable)
	ETaskStatus GetTaskStatus();

	UFUNCTION(BluePrintCallable)
	void SetTaskType(ETaskType InTaskType);

	UFUNCTION(BluePrintCallable)
	ETaskType GetTaskType();

	UFUNCTION(BluePrintCallable)
	bool GetActiveState();

	UFUNCTION()
	bool RollFireChance();

	UFUNCTION()
	void SpawnSmokeVFX();

	UFUNCTION()
	void DespawnSmokeVFX();

	UFUNCTION(BlueprintCallable)
	void SetHasInteractingPlayer(bool InHasPlayer);

	UFUNCTION(BlueprintCallable)
	bool DoesHaveInteractingPlayer();

private:
	ATaskManager* TaskManager;

	ETaskStatus CurrentTaskStatus = ETaskStatus::Idle;

	UPROPERTY(EditAnywhere)
	ETaskType CurrentTaskType = ETaskType::Refuel;

	UPROPERTY()
	bool IsActive = false;

	//Nils took this out
	/*UPROPERTY(EditAnywhere, Category = "VFX")
	UNiagaraSystem* FireVFX = nullptr;*/

	UPROPERTY(EditAnywhere, Category = "VFX")
	TSubclassOf<AActor> SmokeVFXActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "VFX")
	AActor* SpawnedSmokeVFXActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "VFX")
	FRotator SmokeRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	bool HasInteractingPlayer = false;
};
