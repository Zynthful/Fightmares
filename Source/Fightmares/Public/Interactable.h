// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.generated.h"

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
	virtual void DoTapInteract();
	
	virtual void BeginHoldInteract();
	virtual void DoHoldInteract();
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDoTapInteract"), Category = "Interaction")
	void OnDoTapInteract();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnBeginHoldInteract"), Category = "Interaction")
	void OnBeginHoldInteract();
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDoHoldInteract"), Category = "Interaction")
	void OnDoHoldInteract();
};
