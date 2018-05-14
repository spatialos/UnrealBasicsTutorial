// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "HeartbeatRequest.h"

UHeartbeatRequest::UHeartbeatRequest()
{
	Underlying.Reset(new improbable::player::HeartbeatRequest());
}

UHeartbeatRequest* UHeartbeatRequest::Init(const improbable::player::HeartbeatRequest& underlying)
{
    Underlying.Reset(new improbable::player::HeartbeatRequest(underlying));
	return this;
}


improbable::player::HeartbeatRequest UHeartbeatRequest::GetUnderlying()
{
	return *Underlying.Get();
}
