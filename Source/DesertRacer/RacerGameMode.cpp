// Fill out your copyright notice in the Description page of Project Settings.


#include "RacerGameMode.h"

#include "Kismet/GameplayStatics.h"

void ARacerGameMode::ResetLevel(bool IsWin) {
	float ResetTime = LoseResetTime;
	if (IsWin) {
		ResetTime = WinResetTime;
	}

	GetWorldTimerManager().SetTimer(ResetGameTimer, this, &ARacerGameMode::OnResetGameTimerTimeout, 1.0f, false, ResetTime);
}

void ARacerGameMode::OnResetGameTimerTimeout() {
	UGameplayStatics::OpenLevel(GetWorld(), FName("MainLevel"));
}