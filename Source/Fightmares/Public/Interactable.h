// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interactable.generated.h"

class UWidgetComponent;

USTRUCT(BlueprintType)
struct FInteractableData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	float MaxDistance = 25.0f;
};

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

public:
	virtual FInteractableData& GetData() = 0;
	virtual UWidgetComponent* GetTapButtonPromptWidget() = 0;

	virtual void DoTapInteract();
	virtual void BeginHoldInteract();
	virtual void DoHoldInteract();

protected:
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDoTapInteract"), Category = "Interaction")
	void OnDoTapInteract();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnBeginHoldInteract"), Category = "Interaction")
	void OnBeginHoldInteract();
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDoHoldInteract"), Category = "Interaction")
	void OnDoHoldInteract();
};
