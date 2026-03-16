// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskManager.h"
//#include "GameContainerState.h"
#include "TaskBase.h"

// Sets default values
ATaskManager::ATaskManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATaskManager::BeginPlay()
{
	Super::BeginPlay();

	//Nils took this out
	/*GameContainerState = Cast<AGameContainerState>(GetWorld()->GetGameState());

	if (IsValid(GameContainerState))
	{
		UE_LOG(LogTemp, Warning, TEXT("GameContainer Success in TaskManager"));
	}*/

	// setup TaskTimer and TimeBetweenTask
	TimeBetweenTask = 5.f; // repair

	TaskTimer = 0.f; // repair timer
	
	GetAndProcessAllTasksInLevel();
}

// Called every frame
void ATaskManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckShipStatusAndExecuteTasks(DeltaTime);
}

void ATaskManager::GetAndProcessAllTasksInLevel()
{
	TArray<AActor*> Actors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATaskBase::StaticClass(), Actors);

    if (Actors.Num() > 0)
    {
    	for (const auto& actor : Actors)
    	{
    		if (IsValid(actor))
    		{
    			Cast<ATaskBase>(actor)->SetTaskManager(this);
    			Tasks.Add(Cast<ATaskBase>(actor));
    		}
    	}
    }
    UE_LOG(LogTemp, Warning, TEXT("Task amount: %d"), Tasks.Num());
}


void ATaskManager::CheckShipStatusAndExecuteTasks(float InDeltaTime)
{
	//Nils took this out
	//if (IsValid(GameContainerState))
	//{
	//	TArray<ATaskBase*> PossibleTasks;
	//	if (GameContainerState->GetShipHealth() <= 95.f)
	//	{
	//		if (TaskTimer >= TimeBetweenTask) // index 0 is repair task
	//		{
	//			UE_LOG(LogTemp, Warning, TEXT("Trying to refuel repair task, ship health: %d"), GameContainerState->GetShipHealth())

	//			for (const auto& task : Tasks)
	//			{
	//				if (task->GetTaskType() == ETaskType::Repair)
	//					PossibleTasks.Add(task);
	//			}

	//			if (PossibleTasks.Num() > 0)
	//			{
	//				int tries = 0;
	//				int maxTries = PossibleTasks.Num();
	//				while (tries < maxTries)
	//				{
	//					auto temp = PossibleTasks[FMath::RandRange(0, PossibleTasks.Num() - 1)];
	//					// SetActive will be called by the fire when it's put out
	//					if (!temp->GetActiveState())
	//					{
	//						temp->SpawnSmokeVFX();
	//						temp->SetActive(true);
	//						UE_LOG(LogTemp, Warning, TEXT("TaskManager: Task activated"));
	//						break;
	//					}
	//					tries++;
	//				}
	//			}

	//			TaskTimer = 0.f;
	//		}

	//		PossibleTasks.Empty();

	//		TaskTimer += InDeltaTime; // index 0 repair task, could also do static_cast<int>(ETaskType::Repair) but that's adding unnecessary casting
	//	}
	//}
}

void ATaskManager::RetrieveTask(ATaskBase* InTask)
{
	switch (InTask->GetTaskStatus())
	{
	case ETaskStatus::Idle:
		// if the task is IDLE we should not process it and leave it be
		return;
	case ETaskStatus::Success:
		{
			// process the task, modify GameContainerState variables
			if (InTask->GetTaskType() != ETaskType::Refuel)
				InTask->SetActive(false);
		
			TArray<ATaskBase*> PossibleTasks;
		
			for (const auto& task : Tasks)
			{
				if (task->GetTaskType() == ETaskType::Repair)
					PossibleTasks.Add(task);
			}

			// remove the smoke vfx that is spawned on the task
			InTask->DespawnSmokeVFX();

			//Nils took this out
			//switch (InTask->GetTaskType())
			//{
			//	// cast to int using C++ style casting to refrain from sending a float value to a function that takes an int
			//	// this to void number truncating at the function level
			//case ETaskType::Repair: GameContainerState->SetShipHealth(static_cast<int>(GameContainerState->GetShipHealth() + 15)); break;
			//case ETaskType::Refuel: GameContainerState->SetFuel(GameContainerState->GetFuel() + 25); break;
			//case ETaskType::MotorWinding: GameContainerState->SetMotorEnergy(GameContainerState->GetMotorEnergy() + 25); break;
			//default: UE_LOG(LogTemp, Warning, TEXT("Task type not recognized"));
			//}

			//// remove any active tasks that are repair if we're at full hp after successful completion
			//if (GameContainerState->GetShipHealth() >= 100.f)
			//{
			//	for (const auto& task : PossibleTasks)
			//	{
			//		task->SetActive(false);
			//		task->DespawnSmokeVFX();
			//	}
			//}
		}
		break;
	case ETaskStatus::Failed:
		// process the task, no modification to GameContainerState variables, spawn new task at a new location?
		InTask->SetActive(false);
		// remove smoke since upon failure we disable the task
		InTask->DespawnSmokeVFX();
		break;
	case ETaskStatus::Cancelled:
		// process the task, spawn a new task and remove this task
		break;
	}
}