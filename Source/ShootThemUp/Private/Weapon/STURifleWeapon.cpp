// Shoot Them Up Game, All Rights Reserved


#include "Weapon/STURifleWeapon.h"
#include <Engine/World.h>
#include <DrawDebugHelpers.h>

void ASTURifleWeapon::StartFire()
{
	GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &ASTURifleWeapon::MakeShot, TimerBetweenShoot, true);
	MakeShot();
}

void ASTURifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
}

void ASTURifleWeapon::MakeShot()
{
	if (!GetWorld() || IsAmmoEmpty())
	{
		StopFire();
		return;
	}

	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) 
	{
		StopFire();
		return;
	}

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);

	if (HitResult.bBlockingHit)
	{
		MakeDamage(HitResult);
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 2.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
	}
	else
	{
		DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 2.0f);
	}

	DecreaseAmmo();
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	FVector ViewLocation;
	FRotator ViewRotation;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

	TraceStart = ViewLocation;
	const auto HalfRand = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDiraction = FMath::VRandCone(ViewRotation.Vector(), HalfRand);
	TraceEnd = TraceStart + ShootDiraction * TraceMaxDistance;
	return true;
}


void ASTURifleWeapon::MakeDamage(const FHitResult& HitResult)
{
	const auto DamagedActor = HitResult.GetActor();

	if (!DamagedActor) return;
	DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}