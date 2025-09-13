// Fill out your copyright notice in the Description page of Project Settings.
#include "EnhancedInputComponent.h"

#include "PoliticsCharacter.h"

// Sets default values
APoliticsCharacter::APoliticsCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APoliticsCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APoliticsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APoliticsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	UE_LOG(LogTemp, Warning, TEXT("setup"));
	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APoliticsCharacter::HandleMove);
}


void APoliticsCharacter::HandleMove(const FInputActionInstance& Instance)
{
	FVector2D MoveVector = Instance.GetValue().Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("HandleMove"));
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MoveVector.ToString());
	if (!IsValid(Controller) || MoveVector.SizeSquared() <= 0.0f)
		return;

	MoveVector.Normalize();
	
	FVector MovementInputVector = GetActorForwardVector() * MoveVector.X + GetActorRightVector() * MoveVector.Y; 
	AddMovementInput(MovementInputVector);
}
