// Fill out your copyright notice in the Description page of Project Settings.

#include "RacingGameState.h"
#include "RacingPlayerState.h"
#include "cppball.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"

bool ARacingGameState::StartRace_Validate() {
	return true;
}

void ARacingGameState::StartRace_Implementation() {
	for (int i = 0; i < PlayerArray.Num(); i++) {
		Acppball * pawn = Cast<Acppball>(PlayerArray[i]->GetPawn());
		if (pawn->IsLocallyControlled()) {
			pawn->SetActorLocation(m_raceStart);
			Cast<UPrimitiveComponent>(pawn->SphereComponent)->SetPhysicsLinearVelocity(FVector(0,0,0));
			Cast<UPrimitiveComponent>(pawn->SphereComponent)->SetPhysicsAngularVelocityInDegrees(FVector(0,0,0));
			USpringArmComponent * springy = pawn->spring;
			USceneComponent * prim = Cast<USceneComponent>(springy);
			FRotator currentRotation = prim->GetComponentRotation();
			currentRotation.Yaw = 0.0f;
			prim->SetWorldRotation(currentRotation);
		}
	}
	//Start timer
}

bool ARacingGameState::StopRace_Validate() {
	return true;
}
void ARacingGameState::StopRace_Implementation() {
	for (int i = 0; i < PlayerArray.Num(); i++) {
		Acppball * pawn = Cast<Acppball>(PlayerArray[i]->GetPawn());
		if (pawn->IsLocallyControlled()) {
			pawn->SetActorLocation(m_lobbySpawn);
			Cast<UPrimitiveComponent>(pawn->SphereComponent)->SetPhysicsLinearVelocity(FVector(0,0,0));
			Cast<UPrimitiveComponent>(pawn->SphereComponent)->SetPhysicsAngularVelocityInDegrees(FVector(0,0,0));
		}
	}
	//Stop timer
}
