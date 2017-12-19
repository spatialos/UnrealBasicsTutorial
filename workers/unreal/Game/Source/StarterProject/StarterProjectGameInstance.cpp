// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

#include "StarterProjectGameInstance.h"
#include "StarterProject.h"

#include "StarterProjectGameInstance.h"
#include "EntityRegistry.h"
#include "EntityPipeline.h"
#include "SimpleEntitySpawnerBlock.h"
#include "SpatialOS.h"
#include "SpatialOSComponentUpdater.h"

#define ENTITY_BLUEPRINTS_FOLDER "/Game/EntityBlueprints"

UStarterProjectGameInstance::UStarterProjectGameInstance() : SpatialOSInstance(), MetricsReporterHandle(), SpatialOSComponentUpdater()
{
	SpatialOSComponentUpdater = CreateDefaultSubobject<USpatialOSComponentUpdater>(TEXT("SpatialOSComponentUpdater"));
}

UStarterProjectGameInstance::~UStarterProjectGameInstance()
{
}

void UStarterProjectGameInstance::Init()
{
    UGameInstance::Init();

    SpatialOSInstance = NewObject<USpatialOS>(this);

    SpatialOSInstance->OnConnectedDelegate.AddDynamic(this,
                                                      &UStarterProjectGameInstance::OnSpatialOsConnected);
    SpatialOSInstance->OnDisconnectedDelegate.AddDynamic(
        this, &UStarterProjectGameInstance::OnSpatialOsDisconnected);

    EntityRegistry = NewObject<UEntityRegistry>(this);
}

void UStarterProjectGameInstance::Shutdown()
{
    UGameInstance::Shutdown();

    SpatialOSInstance->OnConnectedDelegate.RemoveDynamic(
        this, &UStarterProjectGameInstance::OnSpatialOsConnected);
    SpatialOSInstance->OnDisconnectedDelegate.RemoveDynamic(
        this, &UStarterProjectGameInstance::OnSpatialOsDisconnected);
}

void UStarterProjectGameInstance::ProcessOps(float DeltaTime)
{
    if (SpatialOSInstance != nullptr && SpatialOSInstance->GetEntityPipeline() != nullptr)
    {
		SpatialOSInstance->ProcessOps();
		SpatialOSInstance->GetEntityPipeline()->ProcessOps(SpatialOSInstance->GetView(), SpatialOSInstance->GetConnection(), GetWorld());
		SpatialOSComponentUpdater->UpdateComponents(EntityRegistry, DeltaTime);
    }
}

USpatialOS* UStarterProjectGameInstance::GetSpatialOS()
{
    return SpatialOSInstance;
}

UEntityRegistry* UStarterProjectGameInstance::GetEntityRegistry()
{
    return EntityRegistry;
}

void UStarterProjectGameInstance::OnSpatialOsConnected()
{
    auto EntitySpawnerBlock = NewObject<USimpleEntitySpawnerBlock>();
    EntitySpawnerBlock->Init(EntityRegistry);
    SpatialOSInstance->GetEntityPipeline()->AddBlock(EntitySpawnerBlock);

    TArray<FString> BlueprintPaths;
    BlueprintPaths.Add(TEXT(ENTITY_BLUEPRINTS_FOLDER));

    EntityRegistry->RegisterEntityBlueprints(BlueprintPaths);

    constexpr auto ShouldTimerLoop = true;
    constexpr auto InitialDelay = 2.0f;
    constexpr auto LoopDelay = 2.0f;

    auto MetricsDelegate = FTimerDelegate::CreateLambda([this]() {
        auto Connection = SpatialOSInstance->GetConnection().Pin();

        if (Connection.IsValid())
        {
            Connection->SendMetrics(SpatialOSInstance->GetMetrics());
        }
    });

    GetWorld()->GetTimerManager().SetTimer(MetricsReporterHandle, MetricsDelegate, LoopDelay,
                                           ShouldTimerLoop, InitialDelay);
}

void UStarterProjectGameInstance::OnSpatialOsDisconnected()
{
    GetWorld()->GetTimerManager().ClearTimer(MetricsReporterHandle);
}
