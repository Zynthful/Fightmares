// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"

void IInteractable::DoTapInteract()
{
	if (UObject* ThisObject = Cast<UObject>(this))
	{
		Execute_OnDoTapInteract(ThisObject);
	}
}

void IInteractable::BeginHoldInteract()
{
	if (UObject* ThisObject = Cast<UObject>(this))
	{
		Execute_OnBeginHoldInteract(ThisObject);
	}
}

void IInteractable::DoHoldInteract()
{
	if (UObject* ThisObject = Cast<UObject>(this))
	{
		Execute_OnDoHoldInteract(ThisObject);
	}
}