// Fill out your copyright notice in the Description page of Project Settings.


#include "BedData.h"

float UBedData::GetRestRecoveryInitialDelay() const
{
	return RestRecoveryInitialDelay;
}

float UBedData::GetRestRecoveryTickRate() const
{
	return RestRecoveryTickRate;
}

float UBedData::GetRestRecoveryTickAmount() const
{
	return RestRecoveryTickAmount;
}

int UBedData::GetMaxCharacters() const
{
	return MaxCharacters;
}
