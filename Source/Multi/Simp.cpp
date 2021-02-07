// Fill out your copyright notice in the Description page of Project Settings.

#include "Simp.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASimp::ASimp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UBoxComponent* BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void ASimp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>()->AddTorque({ 1000,1000,1000 });

}

