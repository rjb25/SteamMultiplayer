// Fill out your copyright notice in the Description page of Project Settings.

#include "cppball.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Physics/PhysicsInterfaceCore.h"
#include "Components/PrimitiveComponent.h"
#include "Math/Vector.h"
#include "Kismet/KismetMathLibrary.h"
#include "Materials/Material.h"
#include "Logging/MessageLog.h"

// Sets default values
Acppball::Acppball()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	SphereComponent->SetSimulatePhysics(true);

	// Set this pawn to be controlled by the lowest-numbered player
	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	spring = CreateDefaultSubobject<USpringArmComponent>(TEXT("spring"));
	spring->SetAbsolute(false, true, false);
	spring->SetupAttachment(RootComponent);
	// Create a dummy root component we can attach things to.
	// Create a camera and a visible object
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	// Attach our camera and visible object to our root component. Offset and rotate the camera.
	OurCamera->SetupAttachment(spring);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	if (SphereVisualAsset.Succeeded()) {
		OurVisibleComponent->SetStaticMesh(SphereVisualAsset.Object);
		OurVisibleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		OurVisibleComponent->SetWorldScale3D(FVector(0.8f));
	}
	static ConstructorHelpers::FObjectFinder<UMaterial> BallSkin(TEXT("/Game/StarterContent/Materials/M_Brick_Clay_Beveled.M_Brick_Clay_Beveled"));
	if (BallSkin.Succeeded()) {
		OurVisibleComponent->SetMaterial(0, BallSkin.Object);
	}
}

// Called when the game starts or when spawned
void Acppball::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("hey------------------------------------------------"));
}

// Called every frame
void Acppball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator springRotation = spring->GetComponentRotation();
	
	{
		float side = right + left;
		float ahead = forward + back;
		FVector direction = { ahead, side, 0 };
		FVector nowhere = { 0,0,0 };
		FVector verticalAxis = { 0,0,1 };
		FVector unitDirection = UKismetMathLibrary::GetDirectionUnitVector(nowhere,direction);
		float pushScale = 3000.0;
		FVector rotatedUnitDirection = UKismetMathLibrary::RotateAngleAxis(unitDirection, springRotation.Yaw, verticalAxis);
		OurVisibleComponent->AddForce(DeltaTime * rotatedUnitDirection * pushScale * OurVisibleComponent->GetMass());
		float swap = rotatedUnitDirection.Y;
		rotatedUnitDirection.Y = rotatedUnitDirection.X;
		rotatedUnitDirection.X = swap*(-1);
		float torqueScale = 100000000.0;
		OurVisibleComponent->AddTorqueInRadians(DeltaTime * rotatedUnitDirection * torqueScale);
		float rotation = rotateRight + rotateLeft;
	//UE_LOG(LogTemp, Warning, TEXT("rot %f"), rotation);
		FRotator rotationChange = FRotator(0.0f, 0.0f, 0.0f);
		float rotationScale = 3.0;
		rotationChange.Yaw = rotation * rotationScale;
		USceneComponent * springComponent = CastChecked<USceneComponent>(spring);
		springComponent->AddWorldRotation(rotationChange);
	}
}

// Called to bind functionality to input
void Acppball::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	PlayerInputComponent->BindAxis("Left", this, &Acppball::Move_Left);
	PlayerInputComponent->BindAxis("Right", this, &Acppball::Move_Right);
	PlayerInputComponent->BindAxis("Back", this, &Acppball::Move_Back);
	PlayerInputComponent->BindAxis("Forward", this, &Acppball::Move_Forward);
	PlayerInputComponent->BindAxis("RotateRight", this, &Acppball::Rotate_Right);
	PlayerInputComponent->BindAxis("RotateLeft", this, &Acppball::Rotate_Left);
}

void Acppball::Move_Right(float AxisValue)
{
	right = AxisValue;
}

void Acppball::Move_Left(float AxisValue)
{
	left = AxisValue;
}

void Acppball::Move_Forward(float AxisValue)
{
	forward = AxisValue;
}

void Acppball::Move_Back(float AxisValue)
{
	back = AxisValue;
}
void Acppball::Rotate_Right(float AxisValue)
{
	rotateRight = AxisValue;
}
void Acppball::Rotate_Left(float AxisValue)
{
	rotateLeft = AxisValue;
}
