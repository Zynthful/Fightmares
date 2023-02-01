// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NetComponent.generated.h"

class UNetData;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIGHTMARES_API UNetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Capture(AActor* Actor);
	virtual void FireAll(FVector Direction);
	virtual void FireSingle(FVector Direction);

protected:
	UPROPERTY(EditAnywhere, Category = "Config")
	UNetData* NetData;

	UPROPERTY()
	TArray<AActor*> ActorsInNet;

		
};
