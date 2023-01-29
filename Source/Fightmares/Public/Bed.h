// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "Bed.generated.h"

class UBedData;
class AFMCharacter;

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

	UFUNCTION(BlueprintCallable)
	virtual void Rest(AFMCharacter* TargetCharacter);
	UFUNCTION(BlueprintCallable)
	virtual void StopResting(AFMCharacter* TargetCharacter);
	
	virtual void OnRestTick(AFMCharacter& Character) const;

	// Start IInteractable overrides
public:
	virtual FInteractableData& GetData() override;
	virtual UWidgetComponent* GetTapButtonPromptWidget() override;
protected:
	virtual void DoTapInteract() override;
	virtual void BeginHoldInteract() override;
	virtual void DoHoldInteract() override;
	// End IInteractable overrides

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	UBedData* BedData;
	
	UPROPERTY(BlueprintReadOnly, Category = "Rest")
	FTimerHandle RestingTimerHandle;

	UPROPERTY(BlueprintReadOnly)
	TArray<AFMCharacter*> OccupyingCharacters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FInteractableData InteractableData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	UWidgetComponent* TapButtonPromptWidget;

	UPROPERTY(EditAnywhere)
	USceneComponent* DefaultRoot = nullptr;
};
