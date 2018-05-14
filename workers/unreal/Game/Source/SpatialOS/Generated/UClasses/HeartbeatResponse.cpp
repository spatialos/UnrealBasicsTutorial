// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "HeartbeatResponse.h"

UHeartbeatResponse::UHeartbeatResponse()
{
	Underlying.Reset(new improbable::player::HeartbeatResponse());
}

UHeartbeatResponse* UHeartbeatResponse::Init(const improbable::player::HeartbeatResponse& underlying)
{
    Underlying.Reset(new improbable::player::HeartbeatResponse(underlying));
	return this;
}


improbable::player::HeartbeatResponse UHeartbeatResponse::GetUnderlying()
{
	return *Underlying.Get();
}
