// Copyright Epic Games, Inc. All Rights Reserved.

#include "TictactoeCPPGameMode.h"
#include "TictactoeCPPPlayerController.h"
#include "TictactoeCPPPawn.h"

ATictactoeCPPGameMode::ATictactoeCPPGameMode()
{
	// no pawn by default
	DefaultPawnClass = ATictactoeCPPPawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ATictactoeCPPPlayerController::StaticClass();
}
