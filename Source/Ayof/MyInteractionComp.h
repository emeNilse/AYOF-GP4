#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyInteractionComp.generated.h"

class UCameraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSomethingHit, AActor*, HitActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNothingHit);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AYOF_API UMyInteractionComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMyInteractionComp();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float TraceLength = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bIsLookingAtPawn = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bIsLookingAtItem = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	APawn* PawnLookingAt = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	AActor* ItemLookingAt = nullptr;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnSomethingHit OnSomethingHit;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnNothingHit OnNothingHit;

private:
	UPROPERTY()
	UCameraComponent* Camera = nullptr;

	void HandleHit(AActor* HitActor);

	void HandleNothingHit();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
