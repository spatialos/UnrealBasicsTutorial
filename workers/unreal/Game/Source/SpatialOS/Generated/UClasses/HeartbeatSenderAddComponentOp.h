// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AddComponentOpWrapperBase.h"
#include "SpatialOSWorkerTypes.h"
#include "improbable/player/heartbeat.h"
#include "HeartbeatSenderAddComponentOp.generated.h"

/**
*
*/
UCLASS()
class SPATIALOS_API UHeartbeatSenderAddComponentOp : public UAddComponentOpWrapperBase
{
	GENERATED_BODY()

public:
	UHeartbeatSenderAddComponentOp() {}

    ::worker::Option<improbable::player::HeartbeatSenderData> Data;
private:
};
