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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void serverSetPlayerReady(bool isReady);
	void serverSetPlayerReady_Implementation(bool isReady);
	bool serverSetPlayerReady_Validate(bool isReady);
	bool getPlayerReady();

	UPROPERTY(Replicated)
	bool m_isReady;
};
