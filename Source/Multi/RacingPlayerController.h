// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RacingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MULTI_API ARacingPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	ARacingPlayerController();
	void addHudCreator();
	int m_totalHudCreators;
	int m_countHudCreators;
	

	
};
