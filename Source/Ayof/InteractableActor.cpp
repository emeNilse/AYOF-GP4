// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"
#include "MyPlayerController.h"

DEFINE_LOG_CATEGORY(LogInteractableActor);

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActor::OnInteract_Implementation(AMyPlayerController* interactingPlayer)
{
	UE_LOG(LogInteractableActor, Display, TEXT("OnInteract called from cpp"))
	OnInteractDelegate.Broadcast(this);
}

void AInteractableActor::OnCancel_Implementation(AMyPlayerController* cancelingPlayer)
{
	UE_LOG(LogInteractableActor, Display, TEXT("OnCancel called from cpp"))
		OnCancelDelegate.Broadcast(this);
}

