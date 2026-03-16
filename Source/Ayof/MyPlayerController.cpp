#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "MyInteractionComp.h"
#include "InteractableActor.h"

DEFINE_LOG_CATEGORY(LogMyPlayerController);

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = false;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (InputMappingContext)
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if (IA_Interact)
		{
			EIC->BindAction(IA_Interact, ETriggerEvent::Triggered, this, &AMyPlayerController::Interact);
		}

		if (IA_Cancel)
		{
			EIC->BindAction(IA_Cancel, ETriggerEvent::Triggered, this, &AMyPlayerController::OnIACancel);
		}
	}
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (bIsFirstPossession)
	{
		CharacterPawn = InPawn;
		CurrentPawn = CharacterPawn;
		bIsFirstPossession = false;
		bInCookingStation = false;
		return;
	}

	//bInCookingStation = !bInCookingStation;
}

void AMyPlayerController::Interact()
{
	if (bInCookingStation) 
	{
		OnInteractAtCookingStation();
	} else 
	{
		if (UMyInteractionComp* InteractionComp = CharacterPawn->FindComponentByClass<UMyInteractionComp>())
		{
			if (InteractionComp->bIsLookingAtPawn && InteractionComp->PawnLookingAt)
			{
				SwitchToStation(InteractionComp->PawnLookingAt);
			}
			else if (InteractionComp->bIsLookingAtItem && InteractionComp->ItemLookingAt)
			{
				AInteractableActor* interactable = Cast<AInteractableActor>(InteractionComp->ItemLookingAt);
				UE_LOG(LogMyPlayerController, Display, TEXT("trying to interact with an item named %s"), *InteractionComp->ItemLookingAt->GetFName().ToString());
				if (!interactable) return;
				  //Call function
				interactable->OnInteract(this);
				UE_LOG(LogMyPlayerController, Display, TEXT("it was an interactableActor and we called interactableActor->Interact()"));
			}
		}
	}
}

void AMyPlayerController::OnIACancel()
{
	if (bInCookingStation)
	{
		SwitchToCharacter();
		UE_LOG(LogMyPlayerController, Display, TEXT("switching from cooking station to pawn on IA_Cancel"));
	}
	else
	{
		OnCancelOutsideCookingStation();
	}
}

void AMyPlayerController::OnInteractAtCookingStation_Implementation()
{
	UE_LOG(LogMyPlayerController, Display, TEXT("IA_Interact recieved while possessing a cooking station"));
}

void AMyPlayerController::OnCancelOutsideCookingStation_Implementation()
{
	UE_LOG(LogMyPlayerController, Display, TEXT("IA_Cancel recieved while not possessing a cooking station"));
}

void AMyPlayerController::SwitchToCharacter()
{
	CurrentPawn = CharacterPawn;

	SetViewTargetWithBlend(CurrentPawn, TimeForSwitchingPawns, EViewTargetBlendFunction::VTBlend_Linear);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			UnPossess();
			Possess(CurrentPawn);
			bShowMouseCursor = false;
			bEnableClickEvents = false;
			bEnableMouseOverEvents = false;
			FInputModeGameOnly InputModeGame;
			SetInputMode(InputModeGame);
			bInCookingStation = false;
		}, TimeForSwitchingPawns + 0.1f, false);
}

void AMyPlayerController::SwitchToStation(APawn* TargetPawn)
{
	CurrentPawn = TargetPawn;

	SetViewTargetWithBlend(CurrentPawn, TimeForSwitchingPawns, EViewTargetBlendFunction::VTBlend_Linear);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			UnPossess();
			Possess(CurrentPawn);
			bShowMouseCursor = true;
			bEnableClickEvents = true;
			bEnableMouseOverEvents = true;
			FInputModeGameAndUI InputModeUI;
			InputModeUI.SetHideCursorDuringCapture(false);
			InputModeUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			SetInputMode(InputModeUI);
			bInCookingStation = true;
		}, TimeForSwitchingPawns + 0.1f, false);
}

