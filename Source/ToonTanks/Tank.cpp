// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankPlayerController = Cast<APlayerController>(GetController());
}


// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController) {
		FHitResult HitResult;
		TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 50, 10, FColor::Red, false, -1.f);

		RotateTurret(HitResult.ImpactPoint);
	}
}

APlayerController* ATank::GetTankPlayerController()
{
	return TankPlayerController;
}

void ATank::Move(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Move value %f"), Value);

	if (Value < 0) {
		IsReversing = true;
	}
	else {
		IsReversing = false;
	}

	FVector DeltaLocation = FVector::Zero();
	DeltaLocation.X = Value;
	AddActorLocalOffset(DeltaLocation * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), true);
}

void ATank::Turn(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Turn value %f"), Value);


	FRotator Rotation = FRotator::ZeroRotator;

	if (IsReversing) {
		Rotation.Yaw = -Value;
	}
	else {
		Rotation.Yaw = Value;
	}	

	AddActorLocalRotation(Rotation * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnSpeed, true);
}

