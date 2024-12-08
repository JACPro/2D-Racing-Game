#include "Obstacle.h"

#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	ObstacleSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("ObstacleSprite"));
	ObstacleSprite->SetupAttachment(RootComponent);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OverlapBegin);

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
	RacerGameMode = Cast<ARacerGameMode>(GameMode);
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult) {
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player && Player->CanMove) {
		Player->CanMove = false;

		UGameplayStatics::PlaySound2D(GetWorld(), HitSound);

		RacerGameMode->ResetLevel(IsFinishLine);
	}
}

