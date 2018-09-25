// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "TestGMMC.generated.h"

/**
 *
 */
UCLASS()
class GADEMO_API UTestGMMC : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
			virtual  float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

};
