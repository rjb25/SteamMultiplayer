// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicTrigger.h"
#include "RacingPlayerState.h"
#include "RacingGameState.h"
#include "cppball.h"
#include "Components/BoxComponent.h"

// Sets default values
ABasicTrigger::ABasicTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UBoxComponent * OurTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OurTriggerBox"));
	OurTriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	OurTriggerBox->SetupAttachment(RootComponent);
	OurTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABasicTrigger::OnOverlapBegin);
	OurTriggerBox->OnComponentEndOverlap.AddDynamic(this, &ABasicTrigger::OnOverlapEnd);

}

// Called when the game starts or when spawned
void ABasicTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor * OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
	FString name = OtherActor->GetName();
	FString compname = OtherComp->GetName();
	if (OtherActor && (OtherActor != this) && OtherComp) {
	UE_LOG(LogTemp, Warning, TEXT("hey %s . %s"),*name, *compname);
		Acppball * pawn = Cast<Acppball>(OtherActor);
		ARacingPlayerState * playerState = Cast<ARacingPlayerState>(pawn->GetPlayerState());
		playerState->setStep(m_step);
	}
}
void ABasicTrigger::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor * OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
}
