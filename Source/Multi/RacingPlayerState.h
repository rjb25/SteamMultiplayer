// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "RacingPlayerState.generated.h"

/**
 * 
 */
class UWorld;
UCLASS()
class MULTI_API ARacingPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ARacingPlayerState();
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void serverSetPlayerDone(bool isDone);
	void serverSetPlayerDone_Implementation(bool isDone);
	bool serverSetPlayerDone_Validate(bool isDone);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void serverSetPlayerReady(bool isReady);
	void serverSetPlayerReady_Implementation(bool isReady);
	bool serverSetPlayerReady_Validate(bool isReady);

	bool getPlayerReady();

	bool getPlayerDone();
	void setStep(int step);
	void incTotalSteps();

	UPROPERTY(Replicated)
	bool m_isDone;
	UPROPERTY(Replicated)
	bool m_isReady;
	int m_step;
	int m_lap;
	int m_maxLap;
	int m_totalSteps;
};
