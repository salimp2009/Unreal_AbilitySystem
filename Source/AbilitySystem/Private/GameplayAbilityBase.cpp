// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilityBase.h"
//#include "..\Public\GameplayAbilityBase.h"


FGameplayAbilityInfo UGameplayAbilityBase::GetAbilityInfo()
{
	UGameplayEffect* CooldownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();

	if (CooldownEffect && CostEffect)
	{
		float CoolDownDuration = 0.0f;
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CoolDownDuration);

		float Cost = 0.0f;
		EAbilityCostType CostType;

		if (CostEffect->Modifiers.Num() > 0)
		{
			FGameplayModifierInfo EffectInfo = CostEffect->Modifiers[0];
			EffectInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
			FGameplayAttribute CostAttr = EffectInfo.Attribute;
			FString AttributeName = CostAttr.AttributeName;
			if (AttributeName == "Health")
			{
				CostType = EAbilityCostType::Health;
			} 
			else if (AttributeName == "Mana")
			{
				CostType = EAbilityCostType::Mana;
			}
			else if(AttributeName == "Strength")
			{
				CostType = EAbilityCostType::Strength;
			}
			return FGameplayAbilityInfo(CoolDownDuration, Cost, CostType, UIMaterial, GetClass());
		}
		
	}
	
	return FGameplayAbilityInfo();
}
