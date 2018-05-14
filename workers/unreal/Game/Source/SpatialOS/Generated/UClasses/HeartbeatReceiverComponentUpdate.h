// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ComponentUpdateOpWrapperBase.h"
#include "improbable/player/heartbeat.h"


#include "HeartbeatReceiverComponentUpdate.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UHeartbeatReceiverComponentUpdate : public UComponentUpdateOpWrapperBase
{
    GENERATED_BODY()

  public:
    UHeartbeatReceiverComponentUpdate();
    
	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
	UHeartbeatReceiverComponentUpdate* Init(const improbable::player::HeartbeatReceiver::Update& underlying);
	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
	UHeartbeatReceiverComponentUpdate* Reset();

	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
    const improbable::player::HeartbeatReceiver::Update GetUnderlying();

  private:
    friend class UHeartbeatReceiverComponent;
	friend class UCallbackDispatcher;

	UHeartbeatReceiverComponentUpdate* InitInternal(const improbable::player::HeartbeatReceiver::Update& underlying);
	UHeartbeatReceiverComponentUpdate* ResetInternal();

    const improbable::player::HeartbeatReceiver::Update GetUnderlyingInternal();


    improbable::player::HeartbeatReceiver::Update Underlying;
	static improbable::player::HeartbeatReceiver::Update DefaultUnderlying;
};
