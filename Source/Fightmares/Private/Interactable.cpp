// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

void IInteractable::OnBeginInteract()
{
	GetOnBeginInteractDelegate().Broadcast();
}

void IInteractable::OnInteract()
{
	GetOnInteractDelegate().Broadcast();
}
