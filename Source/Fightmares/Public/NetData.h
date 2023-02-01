// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NetData.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTMARES_API UNetData : public UDataAsset
{
	GENERATED_BODY()

public:
	// Map of attack strength to num entities in net (e.g. 2,6 => 2 entities, 6 attack damage)
	UPROPERTY(EditAnywhere, Category = "Damage")
	TMap<int, float> EntitiesAttackDamageMap;
};
