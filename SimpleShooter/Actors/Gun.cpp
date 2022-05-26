// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleShooter/Actors/Gun.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"


#include "SimpleShooter/Player/ShooterCharacter.h"



// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	auto GunOwner = Cast<APawn>(GetOwner());
	AController* PlayerController = GunOwner->GetController();

	if (GunOwner && PlayerController)
	{
		FVector StartLocation;
		FRotator Rotation;
		// This function uses "Out parameters". This means the vars that are being passed in are being set to a value.
		PlayerController->GetPlayerViewPoint(StartLocation, Rotation);
		FVector EndLocation = StartLocation + Rotation.Vector() * GunRange;
		ShotDirection = -Rotation.Vector();

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());
		return GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_GameTraceChannel1, Params);
	}

	return false;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	//UE_LOG(LogTemp, Warning, TEXT("Shoot"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, GunMesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;
	bool HasHit = GunTrace(Hit, ShotDirection);

	//You can cast to Pawn since AShooterCharacter is a child down the hierarchy
	if (auto GunOwner = Cast<APawn>(GetOwner()))
	{
		if (AController* PlayerController = GunOwner->GetController())
		{
			if (HasHit && HitVfx)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitVfx, Hit.Location, ShotDirection.Rotation());
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSfx, Hit.Location, ShotDirection.Rotation(), .2f);
				if (Hit.GetActor())
				{
					FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr); // Constructor
					Hit.GetActor()->TakeDamage(Damage, DamageEvent, PlayerController, this);
				}
			}
		}
	}
}
