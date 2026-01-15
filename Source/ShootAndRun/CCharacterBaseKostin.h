// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacterBaseKostin.generated.h"

UCLASS()
class SHOOTANDRUN_API ACCharacterBaseKostin : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACCharacterBaseKostin();

protected:
	// Called when the game starts or when spawned
	bool live;
	bool sprint;
	bool right;
	float fMaxWalkSpeed;
	float fMaxWalkSpeedSprint;
	virtual void BeginPlay() override;
	void MoveForward(float Axis);	
	void MoveRight(float Axis);	
	void Around(float Axis);	
	void Pitch(float Axis);	
	void Sprint(float Axis);
	
	//void SprintStop();	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
