// Copyright Epic Games, Inc. All Rights Reserved.

#include "TictactoeCPPBlockGrid.h"
#include "TictactoeCPPBlock.h"
#include "Components/TextRenderComponent.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "PuzzleBlockGrid"

ATictactoeCPPBlockGrid::ATictactoeCPPBlockGrid()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	// Create static mesh component
	ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText0"));
	ScoreText->SetRelativeLocation(FVector(200.f,0.f,0.f));
	ScoreText->SetRelativeRotation(FRotator(90.f,0.f,0.f));
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(0)));
	ScoreText->SetupAttachment(DummyRoot);

	// Set defaults
	Size = 3;
	BlockSpacing = 300.f;

	PrimaryActorTick.bCanEverTick = true;
}


void ATictactoeCPPBlockGrid::BeginPlay()
{
	Super::BeginPlay();

	// Number of blocks
	const int32 NumBlocks = Size * Size;

	// Loop to spawn each block
	for(int32 BlockIndex=0; BlockIndex<NumBlocks; BlockIndex++)
	{
		const float XOffset = (BlockIndex/Size) * BlockSpacing; // Divide by dimension
		const float YOffset = (BlockIndex%Size) * BlockSpacing; // Modulo gives remainder

		// Make position vector, offset from Grid location
		const FVector BlockLocation = FVector(XOffset, YOffset, 0.f) + GetActorLocation();

		// Spawn a block
		//ATictactoeCPPBlock* NewBlock = GetWorld()->SpawnActor<ATictactoeCPPBlock>(BlockLocation, FRotator(0,0,0));
		NewBlock[BlockIndex] = GetWorld()->SpawnActor<ATictactoeCPPBlock>(BlockLocation, FRotator(0,0,0));

		// Tell the block about its owner
		if (NewBlock != nullptr)
		{
			NewBlock[BlockIndex]->SpawnNumber = BlockIndex;
			NewBlock[BlockIndex]->OwningGrid = this;
		}
	}
}

void ATictactoeCPPBlockGrid::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	/*if(Score == 9)
	{
		UE_LOG(LogTemp,Warning,TEXT("Eng Game"));
		GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Blue,TEXT("End"));
	}*/

	if(NewBlock != nullptr)
	{
		if(NewBlock[0]->PlayerUse == 1 && NewBlock[1]->PlayerUse == 1&&NewBlock[2]->PlayerUse == 1)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Yellow,TEXT("Player1 Win"));
		}else if(NewBlock[0]->PlayerUse == 2 && NewBlock[1]->PlayerUse == 2&&NewBlock[2]->PlayerUse == 2)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,TEXT("Player2 Win"));

		}
	}
}


void ATictactoeCPPBlockGrid::AddScore()
{
	// Increment score
	Score++;

	if(player == 1)
	{
		player = 2;
	}else if(player == 2)
	{
		player = 1;
	}
	
	// Update text
	ScoreText->SetText(FText::Format(LOCTEXT("ScoreFmt", "Score: {0}"), FText::AsNumber(Score)));
}

#undef LOCTEXT_NAMESPACE
