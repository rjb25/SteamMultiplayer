/* ReadyZone.h */
#pragma once

#include "Components/ShapeComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReadyZone.generated.h"

/**
 * AReadyZone provides a simple actor that
 * reacts to overlapping actors and fires events on
 * overlap begin and overlap end. The default shape
 * is a box. If other shapes are needed, inherit from
 * it and override SetupShapeComponent().
 *
 * To react to the overlap events, override
 * TriggerCallbackOn() and TriggerCallbackOff().
 */
UCLASS()
class MULTI_API AReadyZone : public AActor
{
	GENERATED_BODY()

public:
	DECLARE_EVENT(AReadyZone, FReadyZoneEvent)
	FReadyZoneEvent TriggerOverlapBeginEvent;
	FReadyZoneEvent TriggerOverlapEndEvent;

	// Sets default values for this actor's properties
	AReadyZone();

protected:

	/** Shape of the trigger volume component. */
	UPROPERTY(VisibleAnywhere, Category = "Setup")
		UShapeComponent* Shape = nullptr;

	/** Defines, to which actor this trigger should react to.
		If nullptr, all actors are accepted. */
	UPROPERTY(EditAnywhere, Category = "Setup")
		AActor* ActorThatTriggers = nullptr;

	UPROPERTY(EditAnywhere, Category = "Geometry")
		FVector TriggerExtent = FVector(50.f, 50.f, 50.f);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	/** Delegate for Shape's overlap begin event. */
	UFUNCTION()
		void OnTriggerOverlapBegin
		(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep, const
			FHitResult& SweepResult
		);

	/** Delegate for Shape's overlap end event. */
	UFUNCTION()
		void OnTriggerOverlapEnd
		(
			UPrimitiveComponent* OverlappedComp,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		);

	/** Creates a custom UShapeComponent to represent
		the trigger volume. */
	UFUNCTION()
		void SetupShapeComponent();

	/** Adds callbacks to the shape component's begin
		and end overlap events. */
	UFUNCTION()
		void BindTriggerCallbacksToShape();

	/** Is run, when OnComponentBeginOverlap() is called.
		Override to add functionality. */
	UFUNCTION()
		virtual void TriggerCallbackOn();

	/** Is run, when OnComponentEndOverlap() is called.
		Override to add functionality. */
	UFUNCTION()
		virtual void TriggerCallbackOff();
};
