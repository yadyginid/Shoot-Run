// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SARWeapon.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "pma/TypeDefs.h"
#include "SARCharacter.generated.h"

UCLASS()
class SHOOTANDRUN_API ASARCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASARCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void HorizontalMove(float value);
	void VerticalMove(float value);

	void HorizontalRotate(float value);
	void VerticalRotate(float value);
	
	void Sprint();
	void StopSprint();
	
	void Attack();
	void NextWeapon();
	void PreviousWeapon();

public:
	UPROPERTY(Blueprintable, BlueprintReadOnly, Category = "Jump")
	bool bInAir;
	
	UPROPERTY(Blueprintable, BlueprintReadOnly, Category = "Sprint")
	bool bSprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Jump|Animation")
	UAnimMontage* JumpAnimation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons")
	TArray<ASARWeapon*> Weapons;
	
private:
	int CurrentWeaponIndex;
};
