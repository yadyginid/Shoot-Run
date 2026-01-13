// Fill out your copyright notice in the Description page of Project Settings.


#include "SARPistol.h"

ASARPistol::ASARPistol()
{
	FireAnimMontage = LoadObject<UAnimMontage>(
		nullptr, TEXT("/Game/Core/Blueprints/Player/Animations/SwatSoldier/AM_Firing_Rifle.AM_Firing_Rifle"));
}
