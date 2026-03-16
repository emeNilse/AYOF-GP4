// Fill out your copyright notice in the Description page of Project Settings.


#include "CookingStation.h"

// Sets default values
ACookingStation::ACookingStation()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACookingStation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACookingStation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACookingStation::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

