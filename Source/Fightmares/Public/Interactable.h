// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeginInteract);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteract);

/**
 * 
 */
UINTERFACE(Blueprintable, BlueprintType)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class IInteractable
{
	GENERATED_BODY()

protected:
	//UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnBeginInteract"), Category = "Interaction")
	UFUNCTION()
	virtual void OnBeginInteract();
	
	//UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnInteract"), Category = "Interaction")
	UFUNCTION()
	virtual void OnInteract();

	virtual FOnBeginInteract GetOnBeginInteractDelegate() = 0;
	virtual FOnInteract GetOnInteractDelegate() = 0;
};
