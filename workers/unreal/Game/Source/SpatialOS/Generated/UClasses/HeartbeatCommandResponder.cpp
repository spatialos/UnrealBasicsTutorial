// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "HeartbeatCommandResponder.h"

#include "SpatialOSWorkerTypes.h"

UHeartbeatCommandResponder::UHeartbeatCommandResponder()
{
}

UHeartbeatCommandResponder* UHeartbeatCommandResponder::Init(
    const TWeakPtr<SpatialOSConnection>& InConnection,
    worker::RequestId<
        worker::IncomingCommandRequest<improbable::player::HeartbeatReceiver::Commands::Heartbeat>> 
	InRequestId,
    UHeartbeatRequest* InRequest, 
	const std::string& InCallerWorkerId
)
{
    Connection = InConnection;
    RequestId = InRequestId;
    Request = InRequest;
	CallerWorkerId = FString(InCallerWorkerId.c_str());
	return this;
}

UHeartbeatRequest* UHeartbeatCommandResponder::GetRequest()
{
	return Request;
}

FString UHeartbeatCommandResponder::GetCallerWorkerId()
{
	return CallerWorkerId;
}

void UHeartbeatCommandResponder::SendResponse(UHeartbeatResponse* response)
{
	auto underlyingResponse = response->GetUnderlying();

	auto LockedConnection = Connection.Pin();

	if(LockedConnection.IsValid())
	{
	    LockedConnection->SendCommandResponse(
			RequestId, improbable::player::HeartbeatReceiver::Commands::Heartbeat::Response(underlyingResponse));
	}
}