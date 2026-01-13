// Fill out your copyright notice in the Description page of Project Settings.


#include "SARCharacterAnimInstance.h"

#include "SARCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void USARCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	SARCharacter = Cast<ASARCharacter, APawn>(TryGetPawnOwner());
}

void USARCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (SARCharacter != nullptr)
	{
		Velocity = SARCharacter->GetVelocity();
		Speed = Velocity.Length();
		Direction = CalculateDirection(Velocity, SARCharacter->GetActorRotation());
		
		SARCharacter->bInAir = SARCharacter->GetCharacterMovement()->IsFalling();
	}
}
