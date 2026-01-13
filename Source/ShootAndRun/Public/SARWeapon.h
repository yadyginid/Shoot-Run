// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SARWeapon.generated.h"

UCLASS()
class SHOOTANDRUN_API ASARWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASARWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animations")
	UAnimMontage* FireAnimMontage;
	
	UFUNCTION(Blueprintable)
	void Fire(ACharacter *Character) const;
};
