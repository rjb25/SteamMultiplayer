// Fill out your copyright notice in the Description page of Project Settings.

#include "RacingGameMode.h"
#include "cppball.h"
#include "RacingGameState.h"
#include "RacingPlayerState.h"
#include "RacingPlayerController.h"
#include "RacingHUD.h"
//#include "Sort.h"
ARacingGameMode::ARacingGameMode() {
	DefaultPawnClass = Acppball::StaticClass();
	GameStateClass = ARacingGameState::StaticClass();
	PlayerStateClass = ARacingPlayerState::StaticClass();
	PlayerControllerClass = ARacingPlayerController::StaticClass();
	//HUDClass = ARacingHUD::BPRacingHUD::StaticClass();
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

void ARacingGameMode::setRacerTime(float time) {

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
	TArray<ARacingPlayerState *> playerPlaces;

	for (int playerIndex = 0; playerIndex < playerArray.Num(); playerIndex++) {
		if (ARacingPlayerState * racer = Cast<ARacingPlayerState>(playerArray[playerIndex])) {
			racer->m_isDone = false;
		    racer->m_isReady = false;
			playerPlaces.Add(racer);
		}
	}
	playerPlaces.Sort([](const ARacingPlayerState& left, const ARacingPlayerState& right) { return left.m_totalTime < right.m_totalTime; });
	for (int placeIndex = 0; placeIndex < playerPlaces.Num(); placeIndex++) {
		playerPlaces[placeIndex]->clientSetPlace(placeIndex+1);
	}

	gameState->StopRace();
	return true;
}
