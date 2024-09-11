
#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsInFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // Get the player pawn (tank

    // Set a timer to check for fire condition
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCodition, FireRate, true);
}

void ATower::CheckFireCodition()
{
    if (Tank == nullptr)
    {
        return;
    }
    // Check if we have a target
    if (bIsInFireRange() && Tank->bIsAlive)
    {
        Fire();
    }
}

bool ATower::bIsInFireRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if (Distance <= FireRange)
        {
            return true;
        }
    }
    return false;
}
