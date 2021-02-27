// Fill out your copyright notice in the Description page of Project Settings.

//This is serverSide code
#include "RacingPlayerState.h"
#include "RacingGameMode.h"
#include "UnrealNetwork.h"
#include "Engine/World.h"
ARacingPlayerState::ARacingPlayerState() {
	m_isReady = false;
}

void ARacingPlayerState::serverSetPlayerReady_Implementation(bool isReady) {
	m_isReady = isReady;
	UWorld * world = GetWorld();
	ARacingGameMode * game = Cast<ARacingGameMode>(world->GetAuthGameMode());
	game->checkAllReady();
}

bool ARacingPlayerState::serverSetPlayerReady_Validate(bool isReady) {
	return true;
}

bool ARacingPlayerState::getPlayerReady() {
	return m_isReady;
}
//Not sure I should be replicating if I am specifically setting it on the server.
void ARacingPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARacingPlayerState, m_isReady);
}
