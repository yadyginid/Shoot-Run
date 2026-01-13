// Fill out your copyright notice in the Description page of Project Settings.


#include "SARCharacter.h"

#include "SARPistol.h"
#include "SARRifle.h"
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
	
	CurrentWeaponIndex = 0;
	
	if (GetWorld() != nullptr)
	{
		ASARPistol* PistolInstance = CreateDefaultSubobject<ASARPistol>(TEXT("Pistol"));
		ASARRifle* RifleInstance = CreateDefaultSubobject<ASARRifle>(TEXT("Rifle"));
		
		Weapons.Add(PistolInstance);
		Weapons.Add(RifleInstance);
	}
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
	
	InputComponent->BindAction("Sprint", IE_Pressed, this, &ASARCharacter::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &ASARCharacter::StopSprint);
	
	InputComponent->BindAction("Attack", IE_Pressed, this, &ASARCharacter::Attack);
	
	InputComponent->BindAction("NextWeapon", IE_Pressed, this, &ASARCharacter::NextWeapon);
	InputComponent->BindAction("PreviousWeapon", IE_Pressed, this, &ASARCharacter::PreviousWeapon);
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
	bSprint = true;
	GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
}

void ASARCharacter::StopSprint()
{
	bSprint = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
}

void ASARCharacter::Attack()
{
	if (!Weapons.IsValidIndex(CurrentWeaponIndex))
		return;	
	
	Weapons[CurrentWeaponIndex]->Fire(this);
}

void ASARCharacter::NextWeapon()
{
	if (!Weapons.IsValidIndex(CurrentWeaponIndex + 1))
	{
		CurrentWeaponIndex = 0;
		return;
	}

	CurrentWeaponIndex++;
}

void ASARCharacter::PreviousWeapon()
{
	if (!Weapons.IsValidIndex(CurrentWeaponIndex - 1))
	{
		CurrentWeaponIndex = Weapons.Num() - 1;
		return;	
	}
	
	CurrentWeaponIndex--;
}
