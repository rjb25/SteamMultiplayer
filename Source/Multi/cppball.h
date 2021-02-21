// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "cppball.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MULTI_API Acppball : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Acppball();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USpringArmComponent* spring;
	UPROPERTY(EditAnywhere)
	UCameraComponent* OurCamera;

	UPROPERTY(EditAnywhere)
    UStaticMeshComponent* OurVisibleComponent;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereComponent;
	
	    //Input functions
    void Move_Right(float AxisValue);
    void Move_Left(float AxisValue);
    void Move_Forward(float AxisValue);
    void Move_Back(float AxisValue);
    void Rotate_Right(float AxisValue);
    void Rotate_Left(float AxisValue);

	float right;
	float left;
	float forward;
	float back;
	float rotateRight;
	float rotateLeft;

};
