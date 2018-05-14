// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "HeartbeatReceiverData.h"

UHeartbeatReceiverData::UHeartbeatReceiverData()
{
	Underlying.Reset(new improbable::player::HeartbeatReceiverData());
}

UHeartbeatReceiverData* UHeartbeatReceiverData::Init(const improbable::player::HeartbeatReceiverData& underlying)
{
    Underlying.Reset(new improbable::player::HeartbeatReceiverData(underlying));
	return this;
}


improbable::player::HeartbeatReceiverData UHeartbeatReceiverData::GetUnderlying()
{
	return *Underlying.Get();
}
