// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayTagActor.h"


// Sets default values
AGameplayTagActor::AGameplayTagActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameplayTagActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameplayTagActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

