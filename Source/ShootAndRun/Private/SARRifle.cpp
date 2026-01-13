// Fill out your copyright notice in the Description page of Project Settings.


#include "SARRifle.h"

ASARRifle::ASARRifle()
{
	FireAnimMontage = LoadObject<UAnimMontage>(
		nullptr, TEXT("/Game/Core/Blueprints/Player/Animations/SwatSoldier/AM_Situps.AM_Situps"));
}
