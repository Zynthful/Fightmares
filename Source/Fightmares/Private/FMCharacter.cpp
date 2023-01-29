// Fill out your copyright notice in the Description page of Project Settings.

#include "Fightmares/Public/FMCharacter.h"

#include "Interactable.h"
#include "Algo/Rotate.h"
#include "Components/WidgetComponent.h"
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

	if (AActor* InteractableActor = GetBestInteractableActor(FindInteractableActors()))
	{
		if (IInteractable* Interactable = Cast<IInteractable>(InteractableActor))
		{
			if (Interactable != CurrentInteractable)
			{
				Interactable->GetTapButtonPromptWidget()->SetVisibility(true);
				CurrentInteractable = Interactable;
			}
		}
	}
	else if (CurrentInteractable != nullptr)
	{
		CurrentInteractable->GetTapButtonPromptWidget()->SetVisibility(false);
		CurrentInteractable = nullptr;
	}
	
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
	FVector Direction = Instance.GetValue().Get<FVector>();
	Direction.Y = -Direction.Y;
	
	// Move character
	AddMovementInput(Direction, MovementInputScalar);
}

void AFMCharacter::Interact(const FInputActionInstance& Instance)
{
	OnTapInteract();
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

TArray<AActor*> AFMCharacter::FindInteractableActors()
{
	TArray<FHitResult> Hits;
	const FVector Start = GetActorLocation();
	const FVector End = GetActorLocation();
	const FQuat Rotation = FQuat::Identity;
	const ECollisionChannel CollisionChannel = ECC_WorldDynamic;
	const FCollisionShape Shape = FCollisionShape::MakeSphere(InteractRadius);
	const FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	const FCollisionResponseParams ResponseParams = FCollisionResponseParams::DefaultResponseParam;
	GetWorld()->SweepMultiByChannel(Hits, Start, End, Rotation, CollisionChannel, Shape, QueryParams, ResponseParams);
	//DrawDebugSphere(GetWorld(), Start, Shape.GetSphereRadius(), InteractRadius, FColor::Purple, false, 0.5f);

	TArray<AActor*> InteractableActors;
	int Count = Hits.Num();
	for (int Index = 0; Index < Count; Index++)
	{
		AActor* Actor = Hits[Index].GetActor();
		if (Cast<IInteractable>(Actor))
		{
			InteractableActors.Add(Actor);
		}
	}
	
	return InteractableActors;
}

AActor* AFMCharacter::GetBestInteractableActor(const TArray<AActor*>& Actors)
{
	AActor* BestInteractableActor = nullptr;
	for (AActor* Actor : Actors)
	{
		if (IInteractable* Interactable = Cast<IInteractable>(Actor))
		{
			if (!BestInteractableActor || Actor->GetDistanceTo(this) < BestInteractableActor->GetDistanceTo(this))
			{
				BestInteractableActor = Actor;
			}
		}
	}
	return BestInteractableActor;
}

void AFMCharacter::OnTapInteract()
{
	if (CurrentInteractable == nullptr)
	{
		return;
	}
	
	CurrentInteractable->DoTapInteract();
}

void AFMCharacter::OnHoldInteract()
{
	if (CurrentInteractable == nullptr)
	{
		return;
	}
	
	CurrentInteractable->DoHoldInteract();
}



