// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "InteractingActor.h"
#include "FMCharacter.generated.h"

class IInteractable;

UCLASS()
class FIGHTMARES_API AFMCharacter : public ACharacter, public IInteractingActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFMCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void SetRest(const float& Value);
	virtual void RecoverRest(const float& Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void Move(const FInputActionInstance& Instance);
	virtual void Interact(const FInputActionInstance& Instance);
	virtual void SwingNet(const FInputActionInstance& Instance);

	virtual void OnSprintActionTriggered(const FInputActionInstance& Instance);
	virtual void OnSprintActionCompleted(const FInputActionInstance& Instance);

	// Start IInteractingActor overrides
protected:
	virtual TArray<AActor*> FindInteractableActors() override;
	//virtual TArray<AActor*> SortInteractableActors(const TArray<AActor*>& Actors) override;
	virtual AActor* GetBestInteractableActor(const TArray<AActor*>& Actors) override;
	virtual void OnTapInteract() override;
	virtual void OnHoldInteract() override;
	// End IInteractingActor overrides
protected:

	// Character Movement
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Movement: Sprinting")
	float MaxSprintSpeed = 1000;

	float OldMaxWalkSpeed;

	// Input Settings
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	float MovementInputScalar = 1;

	// Enhanced Input System
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* SprintInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* InteractInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* SwingNetInputAction;

	// Rest

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rest")
	float Rest;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Rest")
	float MaxRest;

	// Interaction

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	float InteractRadius = 25.0f;

private:
	uint8 bSprinting : 1;
	IInteractable* CurrentInteractable;
	
};