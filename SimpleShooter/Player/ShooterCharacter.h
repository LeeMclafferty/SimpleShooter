// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();

	UFUNCTION(BlueprintPure)
	bool GetIsDead() const { return IsDead; }

	UFUNCTION(BlueprintPure)
	float GetCurrentHealthPercentage() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsDead;

private:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void LookRight(float Value);

	//Controller Specific look functions
	void LookUpRate(float Value);
	void LookRightRate(float Value);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float RotationRate;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

	UPROPERTY()
	class AGun* Gun;

	//Health
	UPROPERTY(EditDefaultsOnly)
	float MaxHp;
	UPROPERTY(VisibleAnywhere)
	float CurrentHp;

	void HandleDeath();
};
