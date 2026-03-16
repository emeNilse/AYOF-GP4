#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UAC_Interaction;

DECLARE_LOG_CATEGORY_EXTERN(LogMyPlayerController, Log, All);

UCLASS()
class AYOF_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

	UPROPERTY(BlueprintReadOnly)
	APawn* CharacterPawn = nullptr;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

	void Interact();
	void OnIACancel();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (ToolTip = "called when interact action is fired and playercontroller is in a cookingstation"))
	void OnInteractAtCookingStation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, meta = (ToolTip = "called when Cancel action is fired and playercontroller is NOT in a cookingstation"))
	void OnCancelOutsideCookingStation();

	UFUNCTION(BlueprintCallable)
	bool GetIsPossessingCookingStation() { return bInCookingStation;}

private:

	UPROPERTY()
	APawn* CurrentPawn = nullptr;

	UPROPERTY()
	bool bIsFirstPossession = true;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_Interact;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* IA_Cancel;

	UPROPERTY(EditAnywhere, Category = "Interaction")
	float TimeForSwitchingPawns = 0.5f;

	
	bool bInCookingStation = false;

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "Forces character controller to retun to possessing the main character pawn. Warning may behave oddly if called when already possessing the main character pawn."))
	void SwitchToCharacter();

	UFUNCTION(BlueprintCallable, meta = (ToolTip = "tries to possess the pawn you send in the function."))
	void SwitchToStation(APawn* TargetPawn);

};
