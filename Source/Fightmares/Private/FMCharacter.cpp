// Fill out your copyright notice in the Description page of Project Settings.

#include "Fightmares/Public/FMCharacter.h"

// Sets default values
AFMCharacter::AFMCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFMCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFMCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	// You can bind to any of the trigger events here by changing the "ETriggerEvent" enum value
	Input->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AFMCharacter::Move);
}

void AFMCharacter::Move(const FInputActionInstance& Instance)
{
	// Get X input
	const FVector Direction = Instance.GetValue().Get<FVector>();

	// Move character
	AddMovementInput(Direction, 1);
}



