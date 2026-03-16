#include "MyInteractionComp.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#define ECC_ItemsToPickUp ECC_GameTraceChannel1

UMyInteractionComp::UMyInteractionComp()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMyInteractionComp::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		ACharacter* Character = Cast<ACharacter>(Owner);
		if (Character)
		{
			Camera = Character->FindComponentByClass<UCameraComponent>();
		}
	}
}

void UMyInteractionComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Camera) { return; }

	FVector Start = Camera->GetComponentLocation();
	FVector ForwardVector = Camera->GetForwardVector();
	FVector End = Start + (ForwardVector * TraceLength);

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(GetOwner());

	FCollisionObjectQueryParams ObjectQuery;
	ObjectQuery.AddObjectTypesToQuery(ECC_Pawn);
	ObjectQuery.AddObjectTypesToQuery(ECC_ItemsToPickUp);

	FHitResult Hit;
	bool bHit = GetWorld()->LineTraceSingleByObjectType(
		Hit,
		Start,
		End,
		ObjectQuery,
		TraceParams
	);

	if (bHit)
	{
		HandleHit(Hit.GetActor());
	}
	else
	{
		HandleNothingHit();
	}
}

void UMyInteractionComp::HandleHit(AActor* HitActor)
{
	if (HitActor)
	{

		if (APawn* HitPawn = Cast<APawn>(HitActor))
		{
			PawnLookingAt = HitPawn;
			bIsLookingAtPawn = true;
			bIsLookingAtItem = false;
		}
		else
		{
			ItemLookingAt = HitActor;
			bIsLookingAtPawn = false;
			bIsLookingAtItem = true;
		}


		OnSomethingHit.Broadcast(HitActor);
	}
}

void UMyInteractionComp::HandleNothingHit()
{
	bIsLookingAtPawn = false;
	bIsLookingAtItem = false;

	OnNothingHit.Broadcast();
}

