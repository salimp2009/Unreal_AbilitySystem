// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "AttributeSetBase.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "BrainComponent.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");

	AttributeSetBaseComp = CreateDefaultSubobject<UAttributeSetBase>("AttributeSetBaseComp");

	bIsDead = false;

	TeamID = 255;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	AttributeSetBaseComp->OnHealthChange.AddDynamic(this, &ACharacterBase::OnHealthChanged);
	AutoDetermineTeamIDbyControllerType();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}



void ACharacterBase::AcquireAbility(TSubclassOf<UGameplayAbility> AbilityToAcquire)
{
	if (AbilitySystemComp)
	{
		if (HasAuthority() && AbilityToAcquire)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAcquire, 1, 0));
		}
		
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

void ACharacterBase::OnHealthChanged(float Health, float MaxHealth)
{
	if (Health <= 0.0f && !bIsDead)
	{
		bIsDead = true;
		Dead();
		BP_Die();
	}
	BP_OnHealthChanged(Health, MaxHealth);
}

bool ACharacterBase::IsOtherHostile(ACharacterBase* Other)
{
	return TeamID != Other->GetTeamID();
}

uint8 ACharacterBase::GetTeamID() const
{
	return TeamID;
}

void ACharacterBase::AutoDetermineTeamIDbyControllerType()
{
	if (GetController() && GetController()->IsPlayerController())
	{
		TeamID = 0;   // TeamID is PlayerController; TODO; Use Enums or unsigned float since 255 limits the player number
	}
}

void ACharacterBase::Dead()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->DisableInput(PC);
	}

	AAIController* AIC= Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBrainComponent()->StopLogic("Dead");
	}
}