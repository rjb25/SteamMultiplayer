// Fill out your copyright notice in the Description page of Project Settings.

#include "AfterBeginPlay.h"

AfterBeginPlay::AfterBeginPlay()
{
	m_hudPartsTotal = 2;
}

void AfterBeginPlay::readyHudPart() {
	m_hudPartsReady++;
	if (m_hudPartsReady > m_hudPartsTotal - 1) {

	}

}
