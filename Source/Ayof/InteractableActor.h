// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

class AMyPlayerController;

DECLARE_LOG_CATEGORY_EXTERN(LogInteractableActor, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteract, AInteractableActor*, SendingActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractComplete, AInteractableActor*, SendingActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractOngoing, AInteractableActor*, SendingActor);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCancel, AInteractableActor*, SendingActor);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSecondaryInteract, AInteractableActor*, SendingActor);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSecondaryInteractOnGoing, AInteractableActor*, SendingActor);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSecondaryInteractComplete, AInteractableActor*, SendingActor);


UCLASS()
class AYOF_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta= (ForceAsFunction, ToolTip = "Cpp default simply broadcasts the OnInteractDelegate, overide to add other behaviors"))
	void OnInteract(AMyPlayerController* interactingPlayer);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (ForceAsFunction, ToolTip = "Cpp default simply broadcasts the OnCancelDelegate, overide to add other behaviors"))
	void OnCancel(AMyPlayerController* cancelingPlayer);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnInteract OnInteractDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnInteractOngoing OnInteractOngoingDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnInteractComplete OnInteractCompleteDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCancel OnCancelDelegate;

	/*UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSecondaryInteract SecondaryInteractDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSecondaryInteractOnGoing SecondaryInteractOngoingDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSecondaryInteractComplete SecondaryInteractCompleteDelegate;*/
};
