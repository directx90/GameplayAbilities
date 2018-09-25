// Fill out your copyright notice in the Description page of Project Settings.

#include "GADemoGEEC.h"
#include <Engine/Engine.h>


void UGADemoGEEC::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	GEngine->AddOnScreenDebugMessage(0, 10, FColor::Red, "UGameplayEffectExecutionCalculation HelloWorld");
	OutExecutionOutput.MarkConditionalGameplayEffectsToTrigger();
}


