// Fill out your copyright notice in the Description page of Project Settings.
#include "HCharacter.h"

#include <string>

// Sets default values
AHCharacter::AHCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// Attach the camera component to our capsule component.
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera slightly above the eyes.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// Enable the pawn to control camera rotation.
	FPSCameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AHCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(isRunning)
	{
		
	}

}

// Called to bind functionality to input
void AHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AHCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHCharacter::MoveRight);

	PlayerInputComponent->BindAxis("TurnX", this, &AHCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AHCharacter::AddControllerPitchInput);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AHCharacter::StartRun);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AHCharacter::StopRun);
}

void AHCharacter::GrabItem()
{
	
}

void AHCharacter::MoveForward(float Value)
{
	float speedRunning;
	if(isRunning)
	{
		speedRunning = 10;
	}else
	{
		speedRunning = 1;
	}
	const FRotator  Rotation = Controller->GetControlRotation();
	const FRotator  Direction(0.f,Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(Direction).GetUnitAxis(EAxis::X);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("%f"),speedRunning));
	AddMovementInput(ForwardDirection*speedRunning,Value);
}

void AHCharacter::MoveRight(float Value)
{
	float speedRunning;
	if(isRunning)
	{
		speedRunning = 10;
	}else
	{
		speedRunning = 1;
	}
	const FRotator  Rotation = Controller->GetControlRotation();
	const FRotator  Direction(0.f,Rotation.Yaw, 0.f);
	const FVector RightDirection = FRotationMatrix(Direction).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection*speedRunning,Value);
}

void AHCharacter::StartRun()
{
	isRunning = true;
}

void AHCharacter::StopRun()
{
	isRunning = false;
}


