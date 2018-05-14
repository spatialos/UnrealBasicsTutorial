// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/player/heartbeat.h"

#include "HeartbeatReceiverData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UHeartbeatReceiverData : public UObject
{
    GENERATED_BODY()

  public:
    UHeartbeatReceiverData();
    UHeartbeatReceiverData* Init(const improbable::player::HeartbeatReceiverData& underlying);


	improbable::player::HeartbeatReceiverData GetUnderlying();

  private:
    TUniquePtr<improbable::player::HeartbeatReceiverData> Underlying;
};

