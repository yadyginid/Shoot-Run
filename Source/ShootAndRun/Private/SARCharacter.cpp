// Fill out your copyright notice in the Description page of Project Settings.


#include "SARCharacter.h"

// Sets default values
ASARCharacter::ASARCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Camera->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	SpringArm->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	SpringArm->TargetArmLength = 300.0f;
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 2;
	SpringArm->CameraLagMaxDistance = 1.5f;

	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraRotationLagSpeed = 4.f;
	SpringArm->CameraLagMaxTimeStep = 1.f;

	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false),
	                          USpringArmComponent::SocketName);

	bJumping = false;
	bFirstPerson = false;
	
	
}

// Called when the game starts or when spawned
void ASARCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASARCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bJumping)
	{
		Jump();
	}
}

// Called to bind functionality to input
void ASARCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Move Left/Right", this, &ASARCharacter::HorizontalMove);
	InputComponent->BindAxis("Move Forward/Backward", this, &ASARCharacter::VerticalMove);
	InputComponent->BindAxis("Look Left/Right", this, &ASARCharacter::HorizontalRotate);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ASARCharacter::CheckJumpInput);
	InputComponent->BindAction("Jump", IE_Released, this, &ASARCharacter::CheckJumpInput);

	InputComponent->BindAxis("Look Up/Down", this, &ASARCharacter::VerticalRotate);

	InputComponent->BindAxis("Zoom", this, &ASARCharacter::Zoom);

	InputComponent->BindAction("ChangeCamera", IE_Pressed, this, &ASARCharacter::SwitchCamera);
}

void ASARCharacter::HorizontalMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void ASARCharacter::VerticalMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void ASARCharacter::HorizontalRotate(float value)
{
	if (value)
	{
		AddActorLocalRotation(FRotator(0.f, value, 0.f));
	}
}

void ASARCharacter::CheckJumpInput()
{
	bJumping = !bJumping;
}

void ASARCharacter::VerticalRotate(float value)
{
	if (value)
	{
		float temp = 0;

		if (bFirstPerson)
		{
			temp = Camera->GetRelativeRotation().Pitch + value;

			if (temp < 65.0f && temp > -65.0f)
			{
				Camera->AddLocalRotation(FRotator(value, 0.0f, 0.0f));
			}
		}
		else
		{
			temp = SpringArm->GetRelativeRotation().Pitch + value;

			if (temp < 25 && temp > -65)
			{
				SpringArm->AddLocalRotation(FRotator(value, 0.f, 0.f));
			}
		}
	}
}

void ASARCharacter::Zoom(float value)
{
	if (value)
	{
		float temp = SpringArm->TargetArmLength + (value * -10);

		if (temp < 310 && temp > 140)
		{
			SpringArm->TargetArmLength = temp;
		}
	}
}

void ASARCharacter::SwitchCamera()
{
	if (bFirstPerson)
	{
		SpringArm->TargetArmLength = 300.f;
		SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
		Camera->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
		Camera->AttachToComponent(SpringArm, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false),
		                          USpringArmComponent::SocketName);
	}
	else
	{
		Camera->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}

	bFirstPerson = !bFirstPerson;
}
