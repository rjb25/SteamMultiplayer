// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RacingGameState.generated.h"

/**
 * 
 */
UCLASS()
class MULTI_API ARacingGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void StartRace();
	bool StartRace_Validate();
	void StartRace_Implementation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector m_raceStart;
};
