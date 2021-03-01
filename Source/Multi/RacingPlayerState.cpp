// Fill out your copyright notice in the Description page of Project Settings.

//This is serverSide code
#include "RacingPlayerState.h"
#include "RacingGameMode.h"
#include "UnrealNetwork.h"
#include "Engine/World.h"
#include "BasicTrigger.h"
#include "Kismet/GameplayStatics.h"
ARacingPlayerState::ARacingPlayerState() {
	m_isReady = false;
	m_isDone = false;
	m_maxLap = 3;
	m_step = 0;
	m_lap = 0;
	m_totalSteps = 3;

}
bool ARacingPlayerState::serverSetPlayerDone_Validate(bool isDone) {
	return true;
}

void ARacingPlayerState::serverSetPlayerDone_Implementation(bool isDone) {
	m_isDone = isDone;
	UWorld * world = GetWorld();
	ARacingGameMode * game = Cast<ARacingGameMode>(world->GetAuthGameMode());
	game->checkAllDone();
}

bool ARacingPlayerState::serverSetPlayerReady_Validate(bool isReady) {
	return true;
}

void ARacingPlayerState::serverSetPlayerReady_Implementation(bool isReady) {
	m_isReady = isReady;
	UWorld * world = GetWorld();
	ARacingGameMode * game = Cast<ARacingGameMode>(world->GetAuthGameMode());
	game->checkAllReady();
}

bool ARacingPlayerState::getPlayerDone() {
	return m_isDone;
}

bool ARacingPlayerState::getPlayerReady() {
	return m_isReady;
}

//Not sure I should be replicating if I am specifically setting it on the server.
void ARacingPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ARacingPlayerState, m_isReady);
	DOREPLIFETIME(ARacingPlayerState, m_isDone);
}

void ARacingPlayerState::BeginPlay() {
	Super::BeginPlay();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasicTrigger::StaticClass(), FoundActors);
	m_totalSteps = FoundActors.Num();
}

//Some of this lap logic should probably be on the server but for now this is fine.
void ARacingPlayerState::setStep(int step) {
	if (m_step == m_totalSteps && step == 1) {
	//UE_LOG(LogTemp, Warning, TEXT("hey%d "), step );
		m_step = step;
		m_lap++;
	}
	if (m_step == step - 1) {
		m_step = step;
	}
	if (m_lap == m_maxLap) {
		serverSetPlayerDone(true);
		m_lap = 0;
		m_step = 0;
	}
}
