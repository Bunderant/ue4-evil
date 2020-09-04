// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "EvilPawn.generated.h"

class UCapsuleComponent;
class UCameraComponent;

UCLASS() class EVIL_API AEvilPawn : public APawn
{
	GENERATED_BODY()

private:
	// PROPERTIES
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 500.0f; // cm/sec
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float SteeringSpeed = 0.5f; // rads/sec
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementAccelerationSpeed = 5.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float SteeringAccelerationSpeed = 5.0f;

	// FUNCTIONS
	void ProcessForwardInput(float Value);
	void ProcessSteeringInput(float Value);
	void UpdatePosition();
	void UpdateRotation();

	// VARIABLES
	FVector TargetVelocity;
	FQuat TargetAngularVelocity;
	FVector Velocity;
	FQuat AngularVelocity;

public:
	// Sets default values for this pawn's properties
	AEvilPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
