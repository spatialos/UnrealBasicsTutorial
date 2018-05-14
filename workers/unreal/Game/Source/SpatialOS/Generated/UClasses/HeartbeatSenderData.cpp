// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "HeartbeatSenderData.h"

UHeartbeatSenderData::UHeartbeatSenderData()
{
	Underlying.Reset(new improbable::player::HeartbeatSenderData());
}

UHeartbeatSenderData* UHeartbeatSenderData::Init(const improbable::player::HeartbeatSenderData& underlying)
{
    Underlying.Reset(new improbable::player::HeartbeatSenderData(underlying));
	return this;
}


improbable::player::HeartbeatSenderData UHeartbeatSenderData::GetUnderlying()
{
	return *Underlying.Get();
}
