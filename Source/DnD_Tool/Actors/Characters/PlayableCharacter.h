// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "PlayableCharacter.generated.h"

UCLASS()
class DND_TOOL_API APlayableCharacter : public APawn
{
	GENERATED_BODY()

public:
	APlayableCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void StartMovement(FVector Location);
	virtual void UpdateMovement(float DeltaTime);

protected:
	virtual void BeginPlay() override;

// VARIABLES
public:
	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		UStaticMeshComponent* StatueBase;

	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		USkeletalMeshComponent* StatueCharacter;

private:
	float CharacterSpeed_Units;
	//float CharacterSpeed_Feet;
	float DistanceLerpSpeed_Units;

	// Movement Tracking
	bool Moving;
	FVector StartLocation;
	FVector EndLocation;
	float MovementLerp;
	float DeltaModifier;

};

