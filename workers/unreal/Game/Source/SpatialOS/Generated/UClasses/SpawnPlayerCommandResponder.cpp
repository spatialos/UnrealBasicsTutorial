// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "SpawnPlayerCommandResponder.h"

#include "SpatialOSWorkerTypes.h"

USpawnPlayerCommandResponder::USpawnPlayerCommandResponder()
{
}

USpawnPlayerCommandResponder* USpawnPlayerCommandResponder::Init(
    const TWeakPtr<SpatialOSConnection>& InConnection,
    worker::RequestId<
        worker::IncomingCommandRequest<improbable::spawner::Spawner::Commands::SpawnPlayer>> 
	InRequestId,
    USpawnPlayerRequest* InRequest, 
	const std::string& InCallerWorkerId
)
{
    Connection = InConnection;
    RequestId = InRequestId;
    Request = InRequest;
	CallerWorkerId = FString(InCallerWorkerId.c_str());
	return this;
}

USpawnPlayerRequest* USpawnPlayerCommandResponder::GetRequest()
{
	return Request;
}

FString USpawnPlayerCommandResponder::GetCallerWorkerId()
{
	return CallerWorkerId;
}

void USpawnPlayerCommandResponder::SendResponse(USpawnPlayerResponse* response)
{
	auto underlyingResponse = response->GetUnderlying();

	auto LockedConnection = Connection.Pin();

	if(LockedConnection.IsValid())
	{
	    LockedConnection->SendCommandResponse(
			RequestId, improbable::spawner::Spawner::Commands::SpawnPlayer::Response(underlyingResponse));
	}
}