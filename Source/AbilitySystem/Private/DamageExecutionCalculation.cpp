// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageExecutionCalculation.h"
#include "AttributeSetBase.h"


struct DamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)

	DamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, AttackDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Armor, Target, true);
	}
};

static DamageStatics& GetDamageStatics()
{
	static DamageStatics DamageStaticsVar;
	return DamageStaticsVar;
}

UDamageExecutionCalculation::UDamageExecutionCalculation()
{
	HealthProperty = FindFieldChecked<UProperty>(UAttributeSetBase::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBase, Health));
	HealthDef = FGameplayEffectAttributeCaptureDefinition(HealthProperty, EGameplayEffectAttributeCaptureSource::Target, true);

	RelevantAttributesToCapture.Add(HealthDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().AttackDamageDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().ArmorDef);
}

void UDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// EXTRA INFO THAT CAN BE CAPTURED TO USE IF NEEDED ; NOT needed in this one;
	//UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	//UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	//const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	//Spec.CapturedSourceTags;
	//FAggregatorEvaluateParameters Params;


	float AttackDamageMagnitude = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().AttackDamageDef, FAggregatorEvaluateParameters(), AttackDamageMagnitude);

	float ArmorMagnitude = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().ArmorDef, FAggregatorEvaluateParameters(), ArmorMagnitude);

	// Calculation of Final Damage; Can be changed as needed
	float FinalDamage = FMath::Clamp(AttackDamageMagnitude - ArmorMagnitude, 0.0f, AttackDamageMagnitude - ArmorMagnitude);
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HealthProperty, EGameplayModOp::Additive, -FinalDamage));
}
