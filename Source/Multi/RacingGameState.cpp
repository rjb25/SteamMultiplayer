// Fill out your copyright notice in the Description page of Project Settings.

#include "RacingGameState.h"
#include "RacingPlayerState.h"
#include "cppball.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"

bool ARacingGameState::StartRace_Validate() {
	return true;
}

void ARacingGameState::StartRace_Implementation() {
	for (int i = 0; i < PlayerArray.Num(); i++) {
		Acppball * pawn = Cast<Acppball>(PlayerArray[i]->GetPawn());
		if (pawn->IsLocallyControlled()) {
			pawn->SetActorLocation(m_raceStart);
			pawn->GetRootComponent()->ComponentVelocity = FVector(0,0,0);
			Cast<UPrimitiveComponent>(pawn->OurVisibleComponent)->SetPhysicsLinearVelocity(FVector(0,0,0));
			Cast<UPrimitiveComponent>(pawn->OurVisibleComponent)->SetPhysicsAngularVelocity(FVector(0,0,0));
		}
	}
	//Start timer
}
