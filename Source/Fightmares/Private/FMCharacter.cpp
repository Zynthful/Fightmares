// Fill out your copyright notice in the Description page of Project Settings.

#include "Fightmares/Public/FMCharacter.h"

#include "Kismet/GameplayStatics.h"

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
	
	if (const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->Player))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (!InputMapping.IsNull())
			{
				InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 100);
			}
		}
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	Input->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AFMCharacter::Move);
	Input->BindAction(InteractInputAction, ETriggerEvent::Triggered, this, &AFMCharacter::Interact);
}

void AFMCharacter::Move(const FInputActionInstance& Instance)
{
	FVector Direction = Instance.GetValue().Get<FVector>();
	Direction.Y = -Direction.Y;
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::Printf(TEXT("eyo we do be schmooving: %s"), *Direction.ToString()));
	} 

	// Move character
	AddMovementInput(Direction, MovementInputScalar);
	
}

void AFMCharacter::Interact(const FInputActionInstance& Instance)
{
	
}



