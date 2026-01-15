// Fill out your copyright notice in the Description page of Project Settings.


#include "CCharacterBaseKostin.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "UniversalObjectLocators/UniversalObjectLocatorUtils.h"

// Sets default values
ACCharacterBaseKostin::ACCharacterBaseKostin()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	live = true;
	sprint = false;
	fMaxWalkSpeed = 600.0f;
	fMaxWalkSpeedSprint = 1200.0f;

}

// Called when the game starts or when spawned
void ACCharacterBaseKostin::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACCharacterBaseKostin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACCharacterBaseKostin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this,&ACCharacterBaseKostin::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ACCharacterBaseKostin::MoveRight);
	PlayerInputComponent->BindAxis("Around",this,&ACCharacterBaseKostin::Around);
	PlayerInputComponent->BindAxis("Pitch",this,&ACCharacterBaseKostin::Pitch);
	PlayerInputComponent->BindAxis("Sprint",this,&ACCharacterBaseKostin::Sprint);
	//PlayerInputComponent->BindAction()
}
//Движение вперед/назад
void ACCharacterBaseKostin::MoveForward(float Axis)
{
	if (Axis && live)
	{
		if (Axis>0.0f && sprint && !right) this->GetCharacterMovement()->MaxWalkSpeed=fMaxWalkSpeedSprint;
		else this->GetCharacterMovement()->MaxWalkSpeed=fMaxWalkSpeed;
		FVector ForwardVector = GetActorForwardVector();
		AddMovementInput(ForwardVector,Axis);
	}
}

//Движение влево/вправо
void ACCharacterBaseKostin::MoveRight(float Axis)
{
	if (Axis && live)
	{
		FVector RightVector = GetActorRightVector();
		AddMovementInput(RightVector,Axis);
		right=true;
	}
	else right=false;
}

//Бег
void ACCharacterBaseKostin::Sprint(float Axis)
{
	if (Axis && live)sprint = true;
	else sprint = false;
}

//Вращение X
void ACCharacterBaseKostin::Around(float Axis)
{
	if (Axis)
	{
		AddControllerYawInput(Axis);
	}
}
//Вращение Y
void ACCharacterBaseKostin::Pitch(float Axis)
{
	if (Axis)
	{
		AddControllerPitchInput(Axis);
	}
}