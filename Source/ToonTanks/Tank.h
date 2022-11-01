// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void HandleDestruction();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* CameraComponent;

	void Move(float Value);

	void Turn(float Value);	

	bool IsReversing = false;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float MoveSpeed = 400;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float TurnSpeed = 100;

	APlayerController* TankPlayerController;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	APlayerController* GetTankPlayerController();

};
