// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GroupBeginPlay.generated.h"

UCLASS()
class MULTI_API AGroupBeginPlay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGroupBeginPlay();
	int m_hudPartsTotal;
	int m_hudPartsReady;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
