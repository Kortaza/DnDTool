// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPawn.h"


// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 300.0f;

	Origin = CreateDefaultSubobject<USceneComponent>(TEXT("Origin"));
	Origin->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Origin);
	SpringArm->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementDirection.Normalize();	// Normalise to get direction without magnitude
	FVector NewLocation = ((Speed * DeltaTime) * MovementDirection) + GetActorLocation();
	SetActorLocation(NewLocation);

	// Reset MovementDirection back to 0.0 for next frame
	MovementDirection = FVector(0.0f, 0.0f, 0.0f);
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//
void ACameraPawn::SetMovement(FVector MoveDir)
{
	MovementDirection += MoveDir;
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}
