// Fill out your copyright notice in the Description page of Project Settings.

#include "Bed.h"

#include "BedData.h"
#include "FMCharacter.h"
#include "Kismet/GameplayStatics.h"

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

void ABed::Rest(AFMCharacter* TargetCharacter)
{
	// put target in bed
	OccupyingCharacters.Add(TargetCharacter);

	// build 'rest' meter
	GetWorldTimerManager().SetTimer(RestingTimerHandle, BedData->GetRestRecoveryTickRate(), true, BedData->GetRestRecoveryInitialDelay());
}

void ABed::StopResting(AFMCharacter* TargetCharacter)
{
	// take target out of bed
	OccupyingCharacters.Remove(TargetCharacter);
	
	// stop building 'rest' meter
	GetWorldTimerManager().ClearTimer(RestingTimerHandle);
}

void ABed::OnRestTick(AFMCharacter& Character) const
{
	Character.RecoverRest(BedData->GetRestRecoveryTickAmount());
}

FInteractableData& ABed::GetData()
{
	return InteractableData;
}

void ABed::DoTapInteract()
{
	IInteractable::DoTapInteract();
	if (AFMCharacter* PlayerCharacter = Cast<AFMCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (OccupyingCharacters.Contains(PlayerCharacter))
		{
			StopResting(PlayerCharacter);
		}
		else
		{
			Rest(PlayerCharacter);
		}
	}
}

void ABed::BeginHoldInteract()
{
	IInteractable::BeginHoldInteract();
}

void ABed::DoHoldInteract()
{
	IInteractable::DoHoldInteract();
}

// Called every frame
void ABed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

