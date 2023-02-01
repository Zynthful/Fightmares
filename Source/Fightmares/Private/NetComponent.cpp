// Fill out your copyright notice in the Description page of Project Settings.


#include "NetComponent.h"
#include "Capturable.h"

// Sets default values for this component's properties
UNetComponent::UNetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNetComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UNetComponent::Capture(AActor* Actor)
{
	if (ActorsInNet.Contains(Actor))
	{
		return;
	}

	if (Cast<ICapturable>(Actor))
	{
		ActorsInNet.Add(Actor);
	}
}

void UNetComponent::FireAll(FVector Direction)
{
	for (AActor* Actor : ActorsInNet)
	{
		if (ICapturable* CapturableActor = Cast<ICapturable>(Actor))
		{
			CapturableActor->FireTowards(Direction);
		}
	}
}

void UNetComponent::FireSingle(FVector Direction)
{
	
}

