// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"

void IInteractable::DoTapInteract()
{
	OnDoTapInteract();
}

void IInteractable::BeginHoldInteract()
{
	OnBeginHoldInteract();
}

void IInteractable::DoHoldInteract()
{
	OnDoHoldInteract();
}