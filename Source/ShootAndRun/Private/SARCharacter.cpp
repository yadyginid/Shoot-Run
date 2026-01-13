// Fill out your copyright notice in the Description page of Project Settings.


#include "SARCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASARCharacter::ASARCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
	SpringArm->bUsePawnControlRotation = true;
	Camera->bUsePawnControlRotation = false;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ASARCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ASARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Move Left/Right", this, &ASARCharacter::HorizontalMove);
	InputComponent->BindAxis("Move Forward/Backward", this, &ASARCharacter::VerticalMove);
	InputComponent->BindAxis("Look Left/Right", this, &ASARCharacter::HorizontalRotate);
	InputComponent->BindAxis("Look Up/Down", this, &ASARCharacter::VerticalRotate);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ASARCharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ASARCharacter::StopJumping);
	
}

void ASARCharacter::HorizontalMove(float value)
{
	if (value)
	{
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void ASARCharacter::VerticalMove(float value)
{
	if (value)
	{
		FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void ASARCharacter::HorizontalRotate(float value)
{
	if (value)
	{
		AddControllerYawInput(value);
	}
}

void ASARCharacter::VerticalRotate(float value)
{
	if (value)
	{
		AddControllerPitchInput(value);
	}
}

void ASARCharacter::Sprint()
{
	//CharacterMovement->MaxWalkSpeed = 10;
}
