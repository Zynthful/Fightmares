// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractingActor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UInteractingActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FIGHTMARES_API IInteractingActor
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable)
	virtual TArray<AActor*> FindInteractableActors() = 0;

	// Sort interactables by highest 'priority' (to determine which interactables we want to interact with the most)
	//UFUNCTION(BlueprintCallable)
	//virtual TArray<AActor>* SortInteractableActors(const TArray<AActor*>& Actors) = 0;

	// Get highest 'priority' interactable
	UFUNCTION(BlueprintCallable)
	virtual AActor* GetBestInteractableActor(const TArray<AActor*>& Actors) = 0;
	
	virtual void OnTapInteract() = 0;
	virtual void OnHoldInteract() = 0;

	virtual void OnBeginHoldInteract();

};
