// Fill out your copyright notice in the Description page of Project Settings.

#include "GroupBeginPlay.h"

// Sets default values
AGroupBeginPlay::AGroupBeginPlay()
{

}

// Called when the game starts or when spawned
void AGroupBeginPlay::BeginPlay()
{
	Super::BeginPlay();
	GetGameInstance();
	
}

// Called every frame
//void AGroupBeginPlay::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);

//}

