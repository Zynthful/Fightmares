// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Bed.generated.h"



UCLASS()
class FIGHTMARES_API ABed : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Start IInteractable overrides
protected:
	virtual void OnBeginInteract() override;
	virtual void OnInteract() override;
public:
	virtual FOnBeginInteract GetOnBeginInteractDelegate() override;
	virtual FOnInteract GetOnInteractDelegate() override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnBeginInteract OnBeginInteractDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteract OnInteractDelegate;
	// End IInteractable overrides

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
