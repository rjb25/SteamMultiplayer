/* SimpleTriggerVolume.cpp */

#include "ReadyZone.h"
#include "Components/BoxComponent.h"

AReadyZone::AReadyZone()
{
	PrimaryActorTick.bCanEverTick = true;

	// Create a separate root component, so the trigger
	// volume may be placed relatively
	RootComponent = CreateDefaultSubobject
		<USceneComponent>(FName("Root Component"));

	SetupShapeComponent();
}

void AReadyZone::BeginPlay()
{
	BeginPlay();
	BindTriggerCallbacksToShape();
}

void AReadyZone::Tick(float DeltaTime)
{
	Tick(DeltaTime);
}

void AReadyZone::SetupShapeComponent()
{
	// Create the trigger subobject and set it up
	auto BoxTrigger = CreateDefaultSubobject
		<UBoxComponent>(FName("Trigger Shape"));
	BoxTrigger->SetBoxExtent(TriggerExtent);
	BoxTrigger->SetGenerateOverlapEvents(true);
	Shape = BoxTrigger;
}

void AReadyZone::BindTriggerCallbacksToShape()
{
	if (Shape)
	{
		// Workaround. Prevents cached constructors to
		// add delegates twice.
		Shape->OnComponentBeginOverlap.RemoveDynamic(
			this, &AReadyZone::OnTriggerOverlapBegin);
		Shape->OnComponentEndOverlap.RemoveDynamic(
			this, &AReadyZone::OnTriggerOverlapEnd);

		Shape->OnComponentBeginOverlap.AddDynamic(
			this, &AReadyZone::OnTriggerOverlapBegin);
		Shape->OnComponentEndOverlap.AddDynamic(
			this, &AReadyZone::OnTriggerOverlapEnd);
	}
}

void AReadyZone::OnTriggerOverlapBegin
(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
) {
	// Prevent self collision and check if only collision
	// to specific actor is wanted.
	if (OtherActor &&
		(OtherActor != this) &&
		(OtherActor == ActorThatTriggers ||
			ActorThatTriggers == nullptr))
	{
		TriggerOverlapBeginEvent.Broadcast();
		TriggerCallbackOn();
	}
}

void AReadyZone::OnTriggerOverlapEnd
(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex
) {
	// Prevent self collision and check if only collision
	// to specific actor is wanted.
	if (OtherActor &&
		(OtherActor != this) &&
		(OtherActor == ActorThatTriggers ||
			ActorThatTriggers == nullptr))
	{
		TriggerOverlapEndEvent.Broadcast();
		TriggerCallbackOff();
	}
}

void AReadyZone::TriggerCallbackOn()
{
	UE_LOG(LogTemp, Warning, TEXT("ReadyZone::TriggerCallbackOn(). To add functionality, override this function."));
}

void AReadyZone::TriggerCallbackOff()
{
	UE_LOG(LogTemp, Warning, TEXT("ReadyZone::TriggerCallbackOff(). To add functionality, override this function."));
}
