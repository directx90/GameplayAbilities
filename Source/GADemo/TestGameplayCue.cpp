#include "TestGameplayCue.h"

bool ATestGameplayCue::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	ActorName = MyTarget->GetName();
	GLog->Log(ActorName);
	GLog->Log(FString::Printf(TEXT("OnActive_Implementation Before %d"), Counter));
	Counter ++;
	GLog->Log(FString::Printf(TEXT("OnActive_Implementation After %d"), Counter));
	return true;
}

bool ATestGameplayCue::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	GLog->Log(ActorName);
	auto CurActorName = MyTarget->GetName();
	GLog->Log(CurActorName);
	GLog->Log(FString::Printf(TEXT("OnRemove_Implementation Before %d"), Counter));
	Counter--;
	GLog->Log(FString::Printf(TEXT("OnRemove_Implementation After %d"), Counter));
	return true;
}
