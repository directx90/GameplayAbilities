// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GADemoGEEC.generated.h"

/**
 *
 */
UCLASS()
class GADEMO_API UGADemoGEEC : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()


		virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;


};
