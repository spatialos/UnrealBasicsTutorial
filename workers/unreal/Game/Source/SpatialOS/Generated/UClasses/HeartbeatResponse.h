// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/player/heartbeat.h"

#include "HeartbeatResponse.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UHeartbeatResponse : public UObject
{
    GENERATED_BODY()

  public:
    UHeartbeatResponse();
    UHeartbeatResponse* Init(const improbable::player::HeartbeatResponse& underlying);


	improbable::player::HeartbeatResponse GetUnderlying();

  private:
    TUniquePtr<improbable::player::HeartbeatResponse> Underlying;
};

