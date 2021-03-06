// Fill out your copyright notice in the Description page of Project Settings.

//This is serverSide code
#include "RacingPlayerState.h"
#include "RacingGameMode.h"
#include "RacingHUD.h"
#include "UnrealNetwork.h"
#include "Engine/World.h"
#include "BasicTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "TempRacingWidget.h"
#include "RacingPlayerController.h"
#include "Components/TextBlock.h"
#include "TempRacingWidget.h"
#include "cppball.h"
#include "RacingGameState.h"
#include"Components/PrimitiveComponent.h"
ARacingPlayerState::ARacingPlayerState() {
	m_isReady = false;
	m_isDone = false;
	m_maxLap = 2;
	m_step = 0;
	m_lap = 0;
	m_totalSteps = 3;
	m_totalTime = 0;
	PrimaryActorTick.bCanEverTick = true;

}
// Called every frame
void ARacingPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(m_timerGoing){
		m_totalTime += DeltaTime;
		
		
		m_tempRacingWidget->setTime(m_totalTime);
	}

}
void ARacingPlayerState::startTimer() {
	m_totalTime = 0;
	m_tempRacingWidget = Cast<UTempRacingWidget>(Cast<ARacingHUD>(Cast<APlayerController>(GetPawn()->GetController())->GetHUD())->m_raceStatsWidget);
	m_timerGoing = true;
}

void ARacingPlayerState::stopTimer() {
	m_timerGoing = false;


}
bool ARacingPlayerState::serverSetPlayerDone_Validate(bool isDone, float time) {
	return true;
}

void ARacingPlayerState::serverSetPlayerDone_Implementation(bool isDone, float time) {
	m_totalTime = time;
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

bool ARacingPlayerState::clientSetPlace_Validate(int place) {
	return true;

}
void ARacingPlayerState::clientSetPlace_Implementation(int place) {
	m_tempRacingWidget->setPlace(place);
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
	/*
		APlayerController * playerController = Cast<APlayerController>(GetPawn()->GetController());
		ARacingHUD * racingHUD = Cast<ARacingHUD>(playerController->GetHUD());
		if (racingHUD) {
			m_tempRacingWidget = Cast<UTempRacingWidget>(racingHUD->m_raceStatsWidget);
		}
		*/
}

//Some of this lap logic should probably be on the server but for now this is fine.
void ARacingPlayerState::setStep(int step) {
	if (m_step == m_totalSteps && step == 1) {
	//UE_LOG(LogTemp, Warning, TEXT("hey%d "), step );
		m_step = step;
		m_lap++;
		m_tempRacingWidget->setLap(m_lap);
	}
	if (m_step == step - 1) {
		m_step = step;
	}
	if (m_lap == m_maxLap) {
		stopTimer();
		serverSetPlayerDone(true,m_totalTime);
		Acppball * pawn = Cast<Acppball>(GetPawn());
		if (pawn->IsLocallyControlled()) {
			pawn->SetActorLocation(Cast<ARacingGameState>(GetWorld()->GetGameState())->m_lobbySpawn);
			Cast<UPrimitiveComponent>(pawn->SphereComponent)->SetPhysicsLinearVelocity(FVector(0,0,0));
			Cast<UPrimitiveComponent>(pawn->SphereComponent)->SetPhysicsAngularVelocityInDegrees(FVector(0,0,0));
		}
		m_lap = 0;
	    m_tempRacingWidget->setLap(m_lap);
		m_step = 0;
	}
}
