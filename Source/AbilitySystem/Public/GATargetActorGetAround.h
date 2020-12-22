// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GATargetActorGetAround.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API AGATargetActorGetAround : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:

	/** Initialize and begin targeting logic  */
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	/** Requesting targeting data, but not necessarily stopping/destroying the task. Useful for external target data requests. */
	virtual void ConfirmTargetingAndContinue() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "FindAround")
	float Radius;

};
