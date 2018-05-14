// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/player/heartbeat.h"

#include "HeartbeatRequest.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UHeartbeatRequest : public UObject
{
    GENERATED_BODY()

  public:
    UHeartbeatRequest();
    UHeartbeatRequest* Init(const improbable::player::HeartbeatRequest& underlying);


	improbable::player::HeartbeatRequest GetUnderlying();

  private:
    TUniquePtr<improbable::player::HeartbeatRequest> Underlying;
};

