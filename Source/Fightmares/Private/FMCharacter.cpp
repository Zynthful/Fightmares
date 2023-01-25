// Fill out your copyright notice in the Description page of Project Settings.

#include "Fightmares/Public/FMCharacter.h"

#include "Interactable.h"
#include "Algo/Rotate.h"
#include "GameFramework/CharacterMovementComponent.h"
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
	Input->BindAction(SprintInputAction, ETriggerEvent::Triggered, this, &AFMCharacter::OnSprintActionTriggered);
	Input->BindAction(SprintInputAction, ETriggerEvent::Completed, this, &AFMCharacter::OnSprintActionCompleted);
	Input->BindAction(InteractInputAction, ETriggerEvent::Triggered, this, &AFMCharacter::Interact);
}

void AFMCharacter::SetRest(const float& Value)
{
	Rest = FMath::Min(Value, MaxRest);
}

void AFMCharacter::RecoverRest(const float& Value)
{
	SetRest(Rest + Value);
}

void AFMCharacter::Move(const FInputActionInstance& Instance)
{
	// TODO: Implement
	uint8 bIsInBed = false;
	if (bIsInBed)
	{
		return;
	}
	
	FVector Direction = Instance.GetValue().Get<FVector>();
	Direction.Y = -Direction.Y;
	
	// Move character
	AddMovementInput(Direction, MovementInputScalar);
	
}

void AFMCharacter::Interact(const FInputActionInstance& Instance)
{
	
}

void AFMCharacter::OnSprintActionTriggered(const FInputActionInstance& Instance)
{
	if (bSprinting)
	{
		return;
	}
	OldMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
	bSprinting = true;
}

void AFMCharacter::OnSprintActionCompleted(const FInputActionInstance& Instance)
{
	if (!bSprinting)
	{
		return;
	}
	bSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = OldMaxWalkSpeed;
}

AActor* AFMCharacter::GetBestInteractable() const
{
	TArray<FHitResult> Hits;
	const FQuat Rotation = FQuat(0, 0, 0, 0);
	const FCollisionShape Shape = FCollisionShape::MakeSphere(InteractRadius);
	const FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	const FCollisionResponseParams ResponseParams = FCollisionResponseParams::DefaultResponseParam;
	GetWorld()->SweepMultiByChannel(Hits, GetActorLocation(), GetActorLocation(), Rotation, ECC_Visibility, Shape, QueryParams, ResponseParams);

	AActor* BestInteractableActor = nullptr;
	for (FHitResult Hit : Hits)
	{
		if (IInteractable* Interactable = Cast<IInteractable>(Hit.GetActor()))
		{
			if (!BestInteractableActor || Hit.GetActor()->GetDistanceTo(this) < BestInteractableActor->GetDistanceTo(this))
			{
				BestInteractableActor = Hit.GetActor();
			}
		}
	}
	
	return BestInteractableActor;
}



