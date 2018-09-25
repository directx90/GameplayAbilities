// Fill out your copyright notice in the Description page of Project Settings.

#include "TestGMMC.h"


float UTestGMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	return Spec.GetLevel() * 2;
}


