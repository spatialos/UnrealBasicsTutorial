// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ComponentUpdateOpWrapperBase.h"
#include "improbable/player/heartbeat.h"


#include "HeartbeatSenderComponentUpdate.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UHeartbeatSenderComponentUpdate : public UComponentUpdateOpWrapperBase
{
    GENERATED_BODY()

  public:
    UHeartbeatSenderComponentUpdate();
    
	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
	UHeartbeatSenderComponentUpdate* Init(const improbable::player::HeartbeatSender::Update& underlying);
	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
	UHeartbeatSenderComponentUpdate* Reset();

	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
    const improbable::player::HeartbeatSender::Update GetUnderlying();

  private:
    friend class UHeartbeatSenderComponent;
	friend class UCallbackDispatcher;

	UHeartbeatSenderComponentUpdate* InitInternal(const improbable::player::HeartbeatSender::Update& underlying);
	UHeartbeatSenderComponentUpdate* ResetInternal();

    const improbable::player::HeartbeatSender::Update GetUnderlyingInternal();


    improbable::player::HeartbeatSender::Update Underlying;
	static improbable::player::HeartbeatSender::Update DefaultUnderlying;
};
