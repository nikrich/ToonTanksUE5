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
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}


// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef) {
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 50, 10, FColor::Red, false, -1.f);

		RotateTurret(HitResult.ImpactPoint);
	}
}	

void ATank::Move(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Move value %f"), Value);

	FVector DeltaLocation = FVector::Zero();
	DeltaLocation.X = Value;
	AddActorLocalOffset(DeltaLocation * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), true);
}

void ATank::Turn(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Turn value %f"), Value);


	FRotator Rotation = FRotator::ZeroRotator;
	Rotation.Yaw = Value;

	AddActorLocalRotation(Rotation * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnSpeed, true);
}