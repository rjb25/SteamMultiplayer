// Fill out your copyright notice in the Description page of Project Settings.

#include "RacingGameMode.h"
#include "cppball.h"
#include "RacingGameState.h"
#include "RacingPlayerState.h"
#include "RacingPlayerController.h"
#include "RacingHUD.h"
ARacingGameMode::ARacingGameMode() {
	DefaultPawnClass = Acppball::StaticClass();
	GameStateClass = ARacingGameState::StaticClass();
	PlayerStateClass = ARacingPlayerState::StaticClass();
	PlayerControllerClass = ARacingPlayerController::StaticClass();
	HUDClass = ARacingHUD::StaticClass();
}

bool ARacingGameMode::checkAllReady() {
	ARacingGameState * gameState = GetGameState<ARacingGameState>();
	TArray<APlayerState *> playerArray = gameState->PlayerArray;
	for (int i = 0; i < playerArray.Num(); i++) {
		if (ARacingPlayerState * racer = Cast<ARacingPlayerState>(playerArray[i])) {
			if (!racer->getPlayerReady()) {
			    return false;
			}
		}
	}
	gameState->StartRace();
	return true;
}

bool ARacingGameMode::checkAllDone() {
	ARacingGameState * gameState = GetGameState<ARacingGameState>();
	TArray<APlayerState *> playerArray = gameState->PlayerArray;
	for (int i = 0; i < playerArray.Num(); i++) {
		if (ARacingPlayerState * racer = Cast<ARacingPlayerState>(playerArray[i])) {
			if (!racer->getPlayerDone()) {
			    return false;
			}
		}
	}
	for (int i = 0; i < playerArray.Num(); i++) {
		if (ARacingPlayerState * racer = Cast<ARacingPlayerState>(playerArray[i])) {
			racer->m_isDone = false;
		    racer->m_isReady = false;
		}
	}
	gameState->StopRace();
	return true;
}
