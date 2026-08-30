// CopyRight © Dead Air Game. All Rights Reserved.


#include "DA_WeaponBase.h"

#include "GameFramework/Character.h"

// Sets default values
ADA_WeaponBase::ADA_WeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void ADA_WeaponBase::StartFire()
{
	bFireInProgress = true;
	GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &ThisClass::MakeShoot, 60.0f / RoundsPerMinute, true);
	MakeShoot();
}

void ADA_WeaponBase::StopFire()
{
	bFireInProgress = false;
	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
}

// Called when the game starts or when spawned
void ADA_WeaponBase::BeginPlay()
{
	Super::BeginPlay();

	checkf(GetOwner() && GetOwner()->IsA<ACharacter>(), TEXT("Owner must be a character!"))
	ResetAddons();
}

void ADA_WeaponBase::MakeShoot()
{
	FVector TraceStart, TraceEnd;
	if (!GetTraceData(TraceStart, TraceEnd)) return;

	FHitResult HitResult;
	MakeHit(HitResult, TraceStart, TraceEnd);
}

void ADA_WeaponBase::MakeHit(FHitResult& OutHitResult, const FVector& OutTraceStart, const FVector& OutTraceEnd)
{
	if (!GetWorld()) return;
	
	FCollisionQueryParams CollisionParams;
	CollisionParams.bReturnPhysicalMaterial = true;
	
	GetWorld()->LineTraceSingleByChannel(OutHitResult, OutTraceStart, OutTraceEnd, ECC_Visibility, CollisionParams);
	DrawDebugLine(GetWorld(), OutTraceStart, OutTraceEnd, FColor::Orange, false, 2.5f, 0, 1.0f);
}

bool ADA_WeaponBase::GetTraceData(FVector& OutTraceStart, FVector& OutTraceEnd) const
{
	const APlayerController* Controller = GetPlayerController();
	if (!Controller) return false;

	const FVector MuzzleLocation = Mesh->GetSocketLocation(MuzzleSocketName);
	
	FVector ViewLocation; FRotator ViewRotation;
	Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	
	OutTraceStart = MuzzleLocation;

	const float HalfRad = FMath::DegreesToRadians(BulletSpread);
	const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
	
	OutTraceEnd = ViewLocation + ShootDirection * MaxShootDistance;

	return true;
}

APlayerController* ADA_WeaponBase::GetPlayerController() const
{
	const ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character) return nullptr;

	return Character->GetController<APlayerController>();
}

// Called every frame
void ADA_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADA_WeaponBase::ResetAddons()
{
	check(Mesh);
	Mesh->HideBoneByName(TEXT("wpn_launcher"), PBO_None);
	Mesh->HideBoneByName(TEXT("wpn_scope"), PBO_None);
	Mesh->HideBoneByName(TEXT("wpn_silencer"), PBO_None);
}

