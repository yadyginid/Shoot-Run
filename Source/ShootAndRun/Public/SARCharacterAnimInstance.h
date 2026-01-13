// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SARCharacterAnimInstance.generated.h"

class ASARCharacter;
/**
 * 
 */
UCLASS()
class SHOOTANDRUN_API USARCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(Blueprintable, BlueprintReadOnly, EditDefaultsOnly)
	ASARCharacter* SARCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Velocity;
};
