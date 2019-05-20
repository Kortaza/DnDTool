// Fill out your copyright notice in the Description page of Project Settings.

#include "GroundTile.h"
#include "Components/StaticMeshComponent.h"
#include "System/Globals.h"


// Sets default values
AGroundTile::AGroundTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Origin = CreateDefaultSubobject<USceneComponent>(TEXT("Origin"));
	Origin->SetupAttachment(RootComponent);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(Origin);
	BaseMesh->SetRelativeLocation(FVector(25.0f, 25.0f, 0.0f));
	BaseMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	BaseMesh->SetCollisionResponseToChannel(ECC_Navigation, ECollisionResponse::ECR_Block);
}

// Called every frame
void AGroundTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called when the game starts or when spawned
void AGroundTile::BeginPlay()
{
	Super::BeginPlay();
	BaseMesh->SetCollisionResponseToChannel(ECC_Navigation, ECollisionResponse::ECR_Block);
}


