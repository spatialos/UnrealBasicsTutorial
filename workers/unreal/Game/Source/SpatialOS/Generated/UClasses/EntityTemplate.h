// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpawnerData.h"
#include "HeartbeatReceiverData.h"
#include "HeartbeatSenderData.h"
#include "EntityAclData.h"
#include "MetadataData.h"
#include "PositionData.h"
#include "PersistenceData.h"
#include "improbable/spawner/spawner.h"
#include "improbable/player/heartbeat.h"
#include "improbable/standard_library.h"
#include "EntityTemplate.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UEntityTemplate : public UObject
{
    GENERATED_BODY()

  public:
    UEntityTemplate();
    UEntityTemplate* Init(const worker::Entity& underlying);

    UFUNCTION(BlueprintCallable, Category = "EntityTemplate")
    UEntityTemplate* AddSpawnerComponent(USpawnerData* data);

    UFUNCTION(BlueprintCallable, Category = "EntityTemplate")
    UEntityTemplate* AddHeartbeatReceiverComponent(UHeartbeatReceiverData* data);

    UFUNCTION(BlueprintCallable, Category = "EntityTemplate")
    UEntityTemplate* AddHeartbeatSenderComponent(UHeartbeatSenderData* data);

    UFUNCTION(BlueprintCallable, Category = "EntityTemplate")
    UEntityTemplate* AddEntityAclComponent(UEntityAclData* data);

    UFUNCTION(BlueprintCallable, Category = "EntityTemplate")
    UEntityTemplate* AddMetadataComponent(UMetadataData* data);

    UFUNCTION(BlueprintCallable, Category = "EntityTemplate")
    UEntityTemplate* AddPositionComponent(UPositionData* data);

    UFUNCTION(BlueprintCallable, Category = "EntityTemplate")
    UEntityTemplate* AddPersistenceComponent(UPersistenceData* data);

    worker::Entity GetUnderlying();

  private:
    worker::Entity Underlying;
};
