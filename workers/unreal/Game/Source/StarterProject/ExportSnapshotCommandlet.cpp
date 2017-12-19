// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

#include "ExportSnapshotCommandlet.h"
#include "StarterProject.h"

#include "EntityBuilder.h"
#include "ExportSnapshotCommandlet.h"
#include "improbable/collections.h"
#include "improbable/standard_library.h"
#include <improbable/spawner/spawner.h>
#include <improbable/player/heartbeat.h>
#include <improbable/worker.h>
#include <array>

using namespace improbable;

using Components =
    worker::Components<spawner::Spawner, Persistence, EntityAcl, Position, Metadata, player::HeartbeatSender, player::HeartbeatReceiver>;

const int g_SpawnerEntityId = 1;
const int g_BotEntityId = 2;

UExportSnapshotCommandlet::UExportSnapshotCommandlet()
{
}

UExportSnapshotCommandlet::~UExportSnapshotCommandlet()
{
}

int32 UExportSnapshotCommandlet::Main(const FString& Params)
{
    FString combinedPath =
        FPaths::Combine(*FPaths::GetPath(FPaths::GetProjectFilePath()), TEXT("../../../snapshots"));
    UE_LOG(LogTemp, Display, TEXT("Combined path %s"), *combinedPath);
    if (FPaths::CollapseRelativeDirectories(combinedPath))
    {
        GenerateSnapshot(combinedPath);
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Path was invalid - snapshot not generated"));
    }

    return 0;
}

void UExportSnapshotCommandlet::GenerateSnapshot(const FString& savePath) const
{
    const FString fullPath = FPaths::Combine(*savePath, TEXT("default.snapshot"));

    std::unordered_map<worker::EntityId, worker::Entity> snapshotEntities;
    snapshotEntities.emplace(std::make_pair(g_SpawnerEntityId, CreateSpawnerEntity()));
	snapshotEntities.emplace(std::make_pair(g_BotEntityId, CreateBotEntity()));
    worker::Option<std::string> Result =
        worker::SaveSnapshot(Components{}, TCHAR_TO_UTF8(*fullPath), snapshotEntities);
    if (!Result.empty())
    {
        std::string ErrorString = Result.value_or("");
        UE_LOG(LogTemp, Display, TEXT("Error: %s"), UTF8_TO_TCHAR(ErrorString.c_str()));
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("Snapshot exported to the path %s"), *fullPath);
    }
}

worker::Entity UExportSnapshotCommandlet::CreateSpawnerEntity() const
{
    const Coordinates initialPosition{0, 0, 0};

    WorkerAttributeSet unrealWorkerAttributeSet{worker::List<std::string>{"UnrealWorker"}};
    WorkerAttributeSet unrealClientAttributeSet{worker::List<std::string>{"UnrealClient"}};

    WorkerRequirementSet unrealWorkerWritePermission{{unrealWorkerAttributeSet}};
    WorkerRequirementSet anyWorkerReadPermission{
        {unrealClientAttributeSet, unrealWorkerAttributeSet}};

    auto snapshotEntity =
        improbable::unreal::FEntityBuilder::Begin()
            .AddPositionComponent(Position::Data{initialPosition}, unrealWorkerWritePermission)
            .AddMetadataComponent(Metadata::Data("Spawner"))
            .SetPersistence(true)
            .SetReadAcl(anyWorkerReadPermission)
            .AddComponent<spawner::Spawner>(spawner::Spawner::Data{}, unrealWorkerWritePermission)
            .Build();

    return snapshotEntity;
}

worker::Entity UExportSnapshotCommandlet::CreateBotEntity() const
{
	const Coordinates initialPosition{ 0, 0, -5 };

	WorkerAttributeSet unrealWorkerAttributeSet{ worker::List<std::string>{"UnrealWorker"} };
	WorkerAttributeSet unrealClientAttributeSet{ worker::List<std::string>{"UnrealClient"} };

	WorkerRequirementSet unrealWorkerWritePermission{ { unrealWorkerAttributeSet } };
	WorkerRequirementSet anyWorkerReadPermission{
		{ unrealClientAttributeSet, unrealWorkerAttributeSet } };

	auto snapshotEntity =
		improbable::unreal::FEntityBuilder::Begin()
		.AddPositionComponent(Position::Data{ initialPosition }, unrealWorkerWritePermission)
		.AddMetadataComponent(Metadata::Data("BP_Bot"))
		.SetPersistence(true)
		.SetReadAcl(anyWorkerReadPermission)
		.Build();

	return snapshotEntity;
}