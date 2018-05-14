// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "HeartbeatSenderComponentUpdate.h"

improbable::player::HeartbeatSender::Update UHeartbeatSenderComponentUpdate::DefaultUnderlying = improbable::player::HeartbeatSender::Update();

UHeartbeatSenderComponentUpdate::UHeartbeatSenderComponentUpdate()
{
}

UHeartbeatSenderComponentUpdate* UHeartbeatSenderComponentUpdate::Init(const improbable::player::HeartbeatSender::Update& underlying)
{
	return InitInternal(underlying);
}

UHeartbeatSenderComponentUpdate* UHeartbeatSenderComponentUpdate::Reset()
{
	return ResetInternal();
}

const improbable::player::HeartbeatSender::Update UHeartbeatSenderComponentUpdate::GetUnderlying()
{
    return GetUnderlyingInternal();
}

UHeartbeatSenderComponentUpdate* UHeartbeatSenderComponentUpdate::InitInternal(const improbable::player::HeartbeatSender::Update& underlying)
{
    Underlying = improbable::player::HeartbeatSender::Update(underlying);
	return this;
}

UHeartbeatSenderComponentUpdate* UHeartbeatSenderComponentUpdate::ResetInternal()
{
	return InitInternal(DefaultUnderlying);
}

const improbable::player::HeartbeatSender::Update UHeartbeatSenderComponentUpdate::GetUnderlyingInternal()
{
    return Underlying;
}
