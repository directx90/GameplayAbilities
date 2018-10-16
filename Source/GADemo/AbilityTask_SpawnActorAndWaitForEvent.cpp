#include "AbilityTask_SpawnActorAndWaitForEvent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"


UAbilityTask_SpawnActorAndWaitForEvent::UAbilityTask_SpawnActorAndWaitForEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{}

void UAbilityTask_SpawnActorAndWaitForEvent::OnGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		FGameplayEventData TempData = *Payload;
		TempData.EventTag = EventTag;

		EventReceived.Broadcast(EventTag, TempData);
	}
}

UAbilityTask_SpawnActorAndWaitForEvent* UAbilityTask_SpawnActorAndWaitForEvent::SpawnActorAndWaitForEvent(
	UGameplayAbility* OwningAbility,
	FName TaskInstanceName,
	FGameplayTagContainer EventTags,
	TSubclassOf<AActor> ActorClass,
	const FTransform& SpawnTransform,
	AActor* Owner)
{
	UAbilityTask_SpawnActorAndWaitForEvent* MyObj = NewAbilityTask<UAbilityTask_SpawnActorAndWaitForEvent>(OwningAbility, TaskInstanceName);
	MyObj->EventTags = EventTags;
	MyObj->ActorClass = ActorClass;
	MyObj->SpawnTransform = SpawnTransform;
	MyObj->Owner = Owner;
	return MyObj;
}

void UAbilityTask_SpawnActorAndWaitForEvent::Activate()
{
	if (Ability == nullptr)
	{
		return;
	}

	if (AbilitySystemComponent)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		EventHandle = AbilitySystemComponent->AddGameplayEventTagContainerDelegate(EventTags, FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &UAbilityTask_SpawnActorAndWaitForEvent::OnGameplayEvent));
		FActorSpawnParameters Param;
		Param.Owner = Owner;
		GetWorld()->SpawnActor(ActorClass, &SpawnTransform, Param);
	}
	else
	{
		ABILITY_LOG(Warning, TEXT("UAbilityTask_SpawnActorAndWaitForEvent called on invalid AbilitySystemComponent"));
	}
}

void UAbilityTask_SpawnActorAndWaitForEvent::OnDestroy(bool AbilityEnded)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->RemoveGameplayEventTagContainerDelegate(EventTags, EventHandle);
	}

	Super::OnDestroy(AbilityEnded);
}
