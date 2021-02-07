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
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	spring = CreateDefaultSubobject<USpringArmComponent>(TEXT("spring"));
	spring->bInheritPitch = false;
	spring->bInheritYaw = false;
	spring->bInheritRoll = false;
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
}

// Called when the game starts or when spawned
void Acppball::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Acppball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	{
		if (!CurrentVelocity.IsZero())
		{
			FVector NewLocation = CurrentVelocity * DeltaTime;
	        OurVisibleComponent->AddForce(NewLocation*3000);
		}
	}

}

// Called to bind functionality to input
void Acppball::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Respond every frame to the values of our two movement axes, "MoveX" and "MoveY".
	PlayerInputComponent->BindAxis("MoveX", this, &Acppball::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &Acppball::Move_YAxis);
}

void Acppball::Move_XAxis(float AxisValue)
{
	// Move at 100 units per second forward or backward
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}

void Acppball::Move_YAxis(float AxisValue)
{
	// Move at 100 units per second right or left
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
}
