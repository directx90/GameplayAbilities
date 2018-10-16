#pragma once

#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_SpawnActorAndWaitForEvent.generated.h"

class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSpawnActorAndWaitForEventDelegate, FGameplayTag, EventTag, FGameplayEventData, EventData);

UCLASS()
class GADEMO_API UAbilityTask_SpawnActorAndWaitForEvent : public UAbilityTask
{
	GENERATED_BODY()

public:
	UAbilityTask_SpawnActorAndWaitForEvent(const FObjectInitializer& ObjectInitializer);
	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;
	UPROPERTY(BlueprintAssignable)
		FSpawnActorAndWaitForEventDelegate EventReceived;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
		static UAbilityTask_SpawnActorAndWaitForEvent* SpawnActorAndWaitForEvent(
			UGameplayAbility* OwningAbility,
			FName TaskInstanceName,
			FGameplayTagContainer EventTags,
			TSubclassOf<AActor> ActorClass,
			const FTransform& SpawnTransform,
			AActor* Owner /*= nullptr*/);

private:
	UPROPERTY()
		FGameplayTagContainer EventTags;
	UPROPERTY()
		TSubclassOf<AActor> ActorClass;
	UPROPERTY()
		FTransform SpawnTransform;
	UPROPERTY()
		AActor* Owner;

	void OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);
	FDelegateHandle EventHandle;
};
