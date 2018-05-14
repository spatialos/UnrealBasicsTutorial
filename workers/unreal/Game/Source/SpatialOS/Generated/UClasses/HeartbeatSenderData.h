// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/player/heartbeat.h"

#include "HeartbeatSenderData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UHeartbeatSenderData : public UObject
{
    GENERATED_BODY()

  public:
    UHeartbeatSenderData();
    UHeartbeatSenderData* Init(const improbable::player::HeartbeatSenderData& underlying);


	improbable::player::HeartbeatSenderData GetUnderlying();

  private:
    TUniquePtr<improbable::player::HeartbeatSenderData> Underlying;
};

