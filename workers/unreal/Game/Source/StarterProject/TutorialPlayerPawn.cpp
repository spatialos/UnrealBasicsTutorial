// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialPlayerPawn.h"


// Sets default values
ATutorialPlayerPawn::ATutorialPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PositionComponent = CreateDefaultSubobject<UPositionComponent>(TEXT("PositionComponent"));
}

// Called when the game starts or when spawned
void ATutorialPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATutorialPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!GetController() && PositionComponent->HasAuthority())
	{
		InitialiseAsOwnPlayer();
	}
}

// Called to bind functionality to input
void ATutorialPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ATutorialPlayerPawn::InitialiseAsOwnPlayer()
{	
	APlayerController* LocalPlayerController = GetWorld()->GetFirstPlayerController();
	if (LocalPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATutorialPlayerPawn::InitialiseAsOwnPlayer error, LocalPlayerController was null"))
			return;
	}

	AController* CurrentController = GetController();
	if (CurrentController != LocalPlayerController)
	{
		if (CurrentController != nullptr)
		{
			CurrentController->UnPossess();
		}

		if (LocalPlayerController->GetPawn() != nullptr)
		{
			LocalPlayerController->UnPossess();
		}

		LocalPlayerController->Possess(this);
		UE_LOG(LogTemp, Log, TEXT("ATutorialPlayerPawn::InitialiseAsOwnPlayer creating own player controller for actor %s"), *GetName())
	}
}
