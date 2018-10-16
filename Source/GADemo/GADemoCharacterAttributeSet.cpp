// Fill out your copyright notice in the Description page of Project Settings.

#include "GADemoCharacterAttributeSet.h"
#include "UnrealNetwork.h"

UGADemoCharacterAttributeSet::UGADemoCharacterAttributeSet()
{
	HP = FGameplayAttributeData(1000);
	Duration = FGameplayAttributeData(2);
	MP = FGameplayAttributeData(1000);
}

void UGADemoCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UGADemoCharacterAttributeSet, HP);
	DOREPLIFETIME(UGADemoCharacterAttributeSet, MP);
}

