// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActar.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class MULTI_API AMyActar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActar();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JSphere")
	USphereComponent* SphereComponent;
	UStaticMeshComponent* SphereVisual;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
