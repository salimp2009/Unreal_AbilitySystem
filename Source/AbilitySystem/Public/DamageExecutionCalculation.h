// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "DamageExecutionCalculation.generated.h"

/**
 * 
 */
UCLASS()
class ABILITYSYSTEM_API UDamageExecutionCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()


public:

	UDamageExecutionCalculation();

	FProperty* HealthProperty;
	FGameplayEffectAttributeCaptureDefinition HealthDef;

	//UFUNCTION(BlueprintNativeEvent, Category = "Calculation")
	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;

	
	// TODO: Change UProperty to FProperty ; the other one depreciate in UE425; to do in AttributeSetBase.h and cpp also
	//FProperty* HealthProperty; 
};
