// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskBase.h"

#include "MovieSceneTracksComponentTypes.h"
#include "TaskManager.h"
#include "Components/SceneComponent.h"

// Sets default values
ATaskBase::ATaskBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATaskBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATaskBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATaskBase::SetTaskManager(ATaskManager* InManager)
{
	TaskManager = InManager;
}

void ATaskBase::SendTaskToManager(ETaskStatus status)
{
	if (IsValid(TaskManager))
	{
		CurrentTaskStatus = status;
		TaskManager->RetrieveTask(this);
	}
}

ETaskStatus ATaskBase::GetTaskStatus()
{
	return CurrentTaskStatus;
}

void ATaskBase::SetTaskType(ETaskType InTaskType)
{
	CurrentTaskType = InTaskType;
}

ETaskType ATaskBase::GetTaskType()
{
	return CurrentTaskType;
}

void ATaskBase::SetActive(bool InActiveState)
{
	IsActive = InActiveState;
}

bool ATaskBase::GetActiveState()
{
	return IsActive;
}

void ATaskBase::SetHasInteractingPlayer(bool InHasPlayer)
{
	HasInteractingPlayer = InHasPlayer;
}

bool ATaskBase::DoesHaveInteractingPlayer()
{
	return HasInteractingPlayer;
}


bool ATaskBase::RollFireChance()
{
	if (FMath::RandRange(0, 100) <= 25)
	{
		//Nils took this out
		if (/*FireVFX && */IsValid(GetWorld()))
		{
			/*UNiagaraComponent* SpawnedComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
				FireVFX,
				GetRootComponent(),
				NAME_None,
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				EAttachLocation::KeepRelativeOffset,
				true);*/

			/*if (IsValid(SpawnedComponent))
			{
				UE_LOG(LogTemp, Display, TEXT("FireVFX Spawned, Component Name: %s"), *SpawnedComponent->GetName());
				UE_LOG(LogTemp, Display, TEXT("Component World: %s"), *SpawnedComponent->GetWorld()->GetFullName());
				UE_LOG(LogTemp, Display, TEXT("Component Location: %s"), *SpawnedComponent->GetComponentLocation().ToString());
				UE_LOG(LogTemp, Display, TEXT("Component Visibility: %s"), SpawnedComponent->IsVisible() ? TEXT("True") : TEXT("False"));
				UE_LOG(LogTemp, Display, TEXT("Component Active: %s"), SpawnedComponent->IsActive() ? TEXT("True") : TEXT("False"));
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Niagara system failed to spawn - SpawnedComponent is null!"));
			}*/
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("FireVFX Failed"));
		}
		return true;	
	}
	return false;
}

void ATaskBase::SpawnSmokeVFX()
{
	//Nils did not take this out
	/*
	if (SmokeVFX && IsValid(GetWorld()))
	{
		SmokeVFXComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
			SmokeVFX,
			GetRootComponent(),
			NAME_None,
			FVector::ZeroVector,
			FRotator::ZeroRotator,
			EAttachLocation::KeepRelativeOffset,
			true);

		if (IsValid(SmokeVFXComponent))
		{
			UE_LOG(LogTemp, Display, TEXT("SmokeVFX Spawned, Component Name: %s"), *SmokeVFXComponent->GetName());
			UE_LOG(LogTemp, Display, TEXT("Component World: %s"), *SmokeVFXComponent->GetWorld()->GetFullName());
			UE_LOG(LogTemp, Display, TEXT("Component Location: %s"), *SmokeVFXComponent->GetComponentLocation().ToString());
			UE_LOG(LogTemp, Display, TEXT("Component Visibility: %s"), SmokeVFXComponent->IsVisible() ? TEXT("True") : TEXT("False"));
			UE_LOG(LogTemp, Display, TEXT("Component Active: %s"), SmokeVFXComponent->IsActive() ? TEXT("True") : TEXT("False"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Niagara system failed to spawn - SpawnedComponent is null!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("SmokeVFX Failed"));
	}
	*/
	
	if (IsValid(SmokeVFXActor))
	{
		SpawnedSmokeVFXActor = GetWorld()->SpawnActor<AActor>(SmokeVFXActor, GetActorLocation(), SmokeRotation);
		if (IsValid(SpawnedSmokeVFXActor))
		{
			SpawnedSmokeVFXActor->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
	}
}

void ATaskBase::DespawnSmokeVFX()
{
	/*
	if (IsValid(SmokeVFXComponent))
	{
		SmokeVFXComponent->DestroyComponent();

		SmokeVFXComponent = nullptr;
	}
	*/

	if (IsValid(SpawnedSmokeVFXActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Despawning Smoke"))
		if (SpawnedSmokeVFXActor->Destroy())
			SpawnedSmokeVFXActor = nullptr;
	}
}
