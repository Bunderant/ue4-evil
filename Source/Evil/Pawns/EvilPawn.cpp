// Fill out your copyright notice in the Description page of Project Settings.

#include "EvilPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "CineCameraComponent.h"

// Sets default values
AEvilPawn::AEvilPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	Camera = CreateDefaultSubobject<UCineCameraComponent>(TEXT("Cinematic Camera"));
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEvilPawn::BeginPlay()
{
	Super::BeginPlay();

	Velocity = FVector::ZeroVector;
	AngularVelocityYaw = 0.0f;
}

// Called every frame
void AEvilPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AngularVelocityYaw = FMath::FInterpTo(AngularVelocityYaw, TargetAngularVelocityYaw, DeltaTime, SteeringAccelerationSpeed);
	if (!FMath::IsNearlyZero(AngularVelocityYaw))
	{
		UpdateRotation();
	}

	Velocity = FMath::VInterpTo(Velocity, TargetVelocity, DeltaTime, MovementAccelerationSpeed);
	if (!Velocity.IsNearlyZero())
	{
		UpdatePosition();
	}
}

// Called to bind functionality to input
void AEvilPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AEvilPawn::ProcessForwardInput);
	PlayerInputComponent->BindAxis("SteerRight", this, &AEvilPawn::ProcessSteeringInput);
}

void AEvilPawn::ProcessForwardInput(float Value)
{
	TargetVelocity = FVector(Value * MovementSpeed, 0.0f, 0.0f);
}

void AEvilPawn::ProcessSteeringInput(float Value)
{
	TargetAngularVelocityYaw = Value * PI * SteeringSpeed;
}

void AEvilPawn::UpdatePosition()
{
	AddActorLocalOffset(Velocity * GetWorld()->DeltaTimeSeconds, true);
}

void AEvilPawn::UpdateRotation()
{
	AddActorLocalRotation(FQuat(GetActorUpVector(), AngularVelocityYaw * GetWorld()->DeltaTimeSeconds), true);
}
