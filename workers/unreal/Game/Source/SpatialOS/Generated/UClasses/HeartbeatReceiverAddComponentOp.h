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
#include "HeartbeatReceiverAddComponentOp.generated.h"

/**
*
*/
UCLASS()
class SPATIALOS_API UHeartbeatReceiverAddComponentOp : public UAddComponentOpWrapperBase
{
	GENERATED_BODY()

public:
	UHeartbeatReceiverAddComponentOp() {}

    ::worker::Option<improbable::player::HeartbeatReceiverData> Data;
private:
};
