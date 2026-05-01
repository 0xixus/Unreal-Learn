// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterSamGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "ShooterSamCharacter.h"
#include "ShooterAI.h"
#include "ShooterSamPlayerController.h"

AShooterSamGameMode::AShooterSamGameMode()
{
	// stub
}

void AShooterSamGameMode::BeginPlay()
{
	Super::BeginPlay();

	AShooterSamCharacter* Player = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAI::StaticClass(), ShooterAIActors);
	EnemyCount = ShooterAIActors.Num();

	for (int32 LoopIndex = 0; LoopIndex < ShooterAIActors.Num(); LoopIndex++)
	{
		AShooterAI* ShooterAI = Cast<AShooterAI>(ShooterAIActors[LoopIndex]);
		if (ShooterAI)
		{
			ShooterAI->StartBehaviorTree(Player);
		}
	}
}

void AShooterSamGameMode::ActorDied(AActor* DeadActor)
{
	bool IsGameOver = false;
	bool IsVictory = false;

	AShooterSamCharacter* Player = Cast<AShooterSamCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (DeadActor == Player)
	{
		IsGameOver = true;
	}
	else
	{
		AShooterSamCharacter* Enemy = Cast<AShooterSamCharacter>(DeadActor);
		if (Enemy)
		{
			--EnemyCount;
			if (EnemyCount == 0)
			{
				IsGameOver = true;
				IsVictory = true;
			}
		}
	}

	if (IsGameOver)
	{
		FString GameOverString = IsVictory ? "Mission Complete!" : "Mission Failed";
		AShooterSamPlayerController* ShooterSamPlayerController = Cast<AShooterSamPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (ShooterSamPlayerController)
		{
			ShooterSamPlayerController->HUDWidget->SetMessageText(GameOverString);
			ShooterSamPlayerController->HUDWidget->MessageTextBlock->SetVisibility(ESlateVisibility::Visible);
			FTimerHandle GameOverTimerHandle;
			GetWorldTimerManager().SetTimer(GameOverTimerHandle, ShooterSamPlayerController,
				&AShooterSamPlayerController::OnCountdownTimerTimeout, 2.0f, false);
		}
		else
		{
			UE_LOG(LogTemp, Display, TEXT("Could not find player controller to display game over message."));
		}
	}
}

