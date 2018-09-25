// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GADemoCharacterAttributeSet.generated.h"

/**
 *
 */
UCLASS()
class GADEMO_API UGADemoCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UGADemoCharacterAttributeSet();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplayAttributeData HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplayAttributeData Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FGameplayAttributeData MP;

};
