// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GADemoAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class GADEMO_API UGADemoAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
	
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override
	{
		TagContainer.Reset();
		//UE_LOG(LogTemp,Log, TEXT("Before Num %d"), TagContainer.Num())
		Super::GetOwnedGameplayTags(TagContainer);
		//UE_LOG(LogTemp, Log, TEXT("After Num %d"), TagContainer.Num())
	}
	
};
