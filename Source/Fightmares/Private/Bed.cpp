// Fill out your copyright notice in the Description page of Project Settings.


#include "Bed.h"

// Sets default values
ABed::ABed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABed::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABed::OnBeginInteract()
{
	IInteractable::OnBeginInteract();
}

void ABed::OnInteract()
{
	IInteractable::OnInteract();
}

FOnBeginInteract ABed::GetOnBeginInteractDelegate()
{
	return OnBeginInteractDelegate;
}

FOnInteract ABed::GetOnInteractDelegate()
{
	return OnInteractDelegate;
}

// Called every frame
void ABed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

