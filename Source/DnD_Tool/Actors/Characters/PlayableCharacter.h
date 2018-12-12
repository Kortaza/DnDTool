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
	// Sets default values for this character's properties
	APlayableCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//
	int GetGridSize() { return kGridSize; }

public:
	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		USceneComponent* Origin;

	UPROPERTY(VisibleAnywhere, Category="Viewport")
		UStaticMeshComponent* StatueCharacter;

	UPROPERTY(VisibleAnywhere, Category = "Viewport")
		UStaticMeshComponent* StatueBase;

private:
	static int kGridSize;
	static float kGridSpeed;
};

