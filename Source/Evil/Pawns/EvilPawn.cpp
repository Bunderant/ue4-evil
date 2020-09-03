// Fill out your copyright notice in the Description page of Project Settings.

#include "EvilPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"

// Sets default values
AEvilPawn::AEvilPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComponent;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEvilPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEvilPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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
	if (!FMath::IsNearlyZero(Value))
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveForward input: %f"), Value);
	}
}

void AEvilPawn::ProcessSteeringInput(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		UE_LOG(LogTemp, Warning, TEXT("SteerRight input: %f"), Value);
	}
}
