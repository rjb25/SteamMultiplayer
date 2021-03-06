// Fill out your copyright notice in the Description page of Project Settings.

#include "RacingHUD.h"
#include "Blueprint/UserWidget.h"
#include "RacingPlayerState.h"
#include "RacingPlayerController.h"
#include "TempRacingWidget.h"
#include "RacingGameState.h"
//#include "UMG.h"

ARacingHUD::ARacingHUD() {

}
void ARacingHUD::BeginPlay() {
	Super::BeginPlay();
	createWidgets();
}

void ARacingHUD::createWidgets() {
		m_raceStatsWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), m_raceStats);
		//woe and suffering
		//Cast<ARacingPlayerState>(GetOwningPlayerController()->GetPawn()->GetPlayerState())->m_tempRacingWidget = Cast<UTempRacingWidget>(m_raceStatsWidget);
		if (m_raceStatsWidget) {
		    m_raceStatsWidget->AddToViewport();
		}
}

