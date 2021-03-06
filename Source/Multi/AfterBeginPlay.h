// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class MULTI_API AfterBeginPlay
{
public:
	AfterBeginPlay();
	~AfterBeginPlay();
	void readyHudPart();
	int m_hudPartsTotal;
	int m_hudPartsReady;
};
