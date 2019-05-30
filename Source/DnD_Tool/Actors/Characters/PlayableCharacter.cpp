// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayableCharacter.h"
#include "PlayableCharController.h"
#include "System/Globals.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Engine.h"

// Sets default values
APlayableCharacter::APlayableCharacter(const FObjectInitializer& ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	CharacterSpeed_Units = 300.0f;
	DistanceLerpSpeed_Units = 300.0f;

	Origin = CreateDefaultSubobject<USceneComponent>(TEXT("Origin"));
	Origin->SetupAttachment(RootComponent);

	StatueBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StatueBase"));
	StatueBase->SetupAttachment(Origin);
	StatueBase->SetRelativeLocation(FVector(0.0f, 0.0f, 0.005f));
	StatueBase->SetRelativeScale3D(FVector(0.45f, 0.45f, 0.01f));

	StatueCharacter = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("StatueCharacter"));
	StatueCharacter->SetupAttachment(Origin);
	StatueCharacter->SetRelativeLocation(FVector(0.0f, 0.0f, 1.0f));
	StatueCharacter->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
}

// Called every frame
void APlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovement(DeltaTime);
}

//
void APlayableCharacter::StartMovement(FVector Location)
{
	// Set Location start/end and reset movement variables
	EndLocation = Location;
	StartLocation = GetActorLocation();
	Moving = true;
	MovementLerp = 0.0f;

	// Set the modifier for the deltaTime based on the distance moved and the lerp speed of the character
	DeltaModifier = (EndLocation - StartLocation).Size() / DistanceLerpSpeed_Units;
}

//
void APlayableCharacter::UpdateMovement(float DeltaTime)
{
	if (Moving == false)
	{
		return;	// Return out if not moving
	}

	// Calculate the new MovementLerp and clamp to prevent overshooting
	MovementLerp += DeltaTime / DeltaModifier;
	MovementLerp = FMath::Clamp(MovementLerp, 0.0f, 1.0f);

	// Set the actors new location
	SetActorLocation(FMath::Lerp(StartLocation, EndLocation, MovementLerp));

	if (MovementLerp >= 1.0f)
	{
		Moving = false;	// Stop moving once destination has been reached
	}
}

bool APlayableCharacter::FindPath(AGround* Ground, FNavigatableTile* Destination)
{
	if (Pathfinder)
	{
		delete Pathfinder;
	}
	Pathfinder = new Pathfinding();
	std::vector<FNavigatableTile*> Path = Pathfinder->Start(Ground, CurrentTile, Destination);
	if (Path.size() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "NO PATH FOUND");	
	}
	else
	{
		CurrentTile = Destination;
	}

	// Remove
	return false;
}

bool APlayableCharacter::TraversePath(float DeltaTime)
{
	// Remove
	return false;
}

// Called when the game starts or when spawned
void APlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		FHitResult HitResult;
		FVector StartLoc = GetActorLocation();
		FVector EndLoc = StartLoc + (-GetActorUpVector() * 10000.0f);
		if (World->LineTraceSingleByChannel(HitResult, StartLoc, EndLoc, ECC_Navigation))
		{
			AGround* Ground = Cast<AGround>(HitResult.Actor);
			if (Ground)
			{
				CurrentTile = Ground->FindNavigatableTile(HitResult.Location);
				SetActorLocation(CurrentTile->CentreWorldLocation);
			}
		}
	}
}
