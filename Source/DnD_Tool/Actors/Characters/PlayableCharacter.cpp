// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableCharacter.h"
#include <ConstructorHelpers.h>

#include <Components/StaticMeshComponent.h>

// Static Variables
int APlayableCharacter::kGridSize = 100;
float APlayableCharacter::kGridSpeed = 2.0f * APlayableCharacter::kGridSize;

// Sets default values
APlayableCharacter::APlayableCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//
	Origin = CreateDefaultSubobject<USceneComponent>(TEXT("Origin"));
	Origin->SetupAttachment(RootComponent);
	StatueBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StatueBase"));
	StatueBase->SetupAttachment(Origin);
	StatueCharacter = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StatueCharacter"));
	StatueCharacter->SetupAttachment(StatueBase);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	StatueBase->SetStaticMesh(CubeAsset.Object);
	StatueBase->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.1f));
	StatueBase->SetRelativeLocation(FVector(0.0f, 0.05f, 0.0f));
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayableCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

