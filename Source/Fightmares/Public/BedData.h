// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BedData.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTMARES_API UBedData : public UDataAsset
{
	GENERATED_BODY()

public:
	float GetRestRecoveryInitialDelay() const;
	float GetRestRecoveryTickRate() const;
	float GetRestRecoveryTickAmount() const;
	int GetMaxCharacters() const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rest Recovery")
	float RestRecoveryInitialDelay = 0.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rest Recovery")
	float RestRecoveryTickRate = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rest Recovery")
	float RestRecoveryTickAmount = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	int MaxCharacters = 1;
};
