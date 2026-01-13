// Fill out your copyright notice in the Description page of Project Settings.


#include "SARWeapon.h"

#include "GameFramework/Character.h"

// Sets default values
ASARWeapon::ASARWeapon()
{
}

// Called when the game starts or when spawned
void ASARWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ASARWeapon::Fire(ACharacter* Character) const
{
	// Запускаем анимацию через PlayAnimMontage
	if (FireAnimMontage == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Null FireAnimMontage"));
		return;
	}

	if (Character == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Null Owner Character"));
		return;
	}

	Character->PlayAnimMontage(FireAnimMontage, 1.0f);
}
