// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AGun();
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, Category = "VFX")
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "VFX")
	class UParticleSystem* HitVfx;

	UPROPERTY(EditAnywhere)
	float GunRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 10;


};
