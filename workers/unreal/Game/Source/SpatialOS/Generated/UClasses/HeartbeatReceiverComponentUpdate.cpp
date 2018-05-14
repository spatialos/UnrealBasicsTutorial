// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "HeartbeatReceiverComponentUpdate.h"

improbable::player::HeartbeatReceiver::Update UHeartbeatReceiverComponentUpdate::DefaultUnderlying = improbable::player::HeartbeatReceiver::Update();

UHeartbeatReceiverComponentUpdate::UHeartbeatReceiverComponentUpdate()
{
}

UHeartbeatReceiverComponentUpdate* UHeartbeatReceiverComponentUpdate::Init(const improbable::player::HeartbeatReceiver::Update& underlying)
{
	return InitInternal(underlying);
}

UHeartbeatReceiverComponentUpdate* UHeartbeatReceiverComponentUpdate::Reset()
{
	return ResetInternal();
}

const improbable::player::HeartbeatReceiver::Update UHeartbeatReceiverComponentUpdate::GetUnderlying()
{
    return GetUnderlyingInternal();
}

UHeartbeatReceiverComponentUpdate* UHeartbeatReceiverComponentUpdate::InitInternal(const improbable::player::HeartbeatReceiver::Update& underlying)
{
    Underlying = improbable::player::HeartbeatReceiver::Update(underlying);
	return this;
}

UHeartbeatReceiverComponentUpdate* UHeartbeatReceiverComponentUpdate::ResetInternal()
{
	return InitInternal(DefaultUnderlying);
}

const improbable::player::HeartbeatReceiver::Update UHeartbeatReceiverComponentUpdate::GetUnderlyingInternal()
{
    return Underlying;
}
