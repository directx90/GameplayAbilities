// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"
#include "GameplayTagContainer.h"
#include "TestGameplayCue.generated.h"

/**
 *
 */
UCLASS()
class GADEMO_API ATestGameplayCue : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

public:
	int Counter = 0;
	FString ActorName;
	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

};
