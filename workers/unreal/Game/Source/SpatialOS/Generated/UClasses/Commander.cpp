// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 
#include "Commander.h"
#include "RequestId.h"
#include "SpawnPlayerResponse.h"
#include "HeartbeatResponse.h"
#include "SpawnPlayerRequest.h"
#include "HeartbeatRequest.h"
#include "SpatialOSCommandResult.h"
#include "SpatialOsComponent.h"
#include "SpatialOSViewTypes.h"
#include "SpatialOSWorkerTypes.h"

ECommandResponseCode UCommander::GetCommandResponseCode(const worker::StatusCode UnderlyingStatusCode)
{
	switch (UnderlyingStatusCode)
	{
		case worker::StatusCode::kSuccess:
			return ECommandResponseCode::Success;
		case worker::StatusCode::kTimeout:
			return ECommandResponseCode::Timeout;
		case worker::StatusCode::kNotFound:
			return ECommandResponseCode::NotFound;
		case worker::StatusCode::kAuthorityLost:
			return ECommandResponseCode::AuthorityLost;
		case worker::StatusCode::kPermissionDenied:
			return ECommandResponseCode::PermissionDenied;
		case worker::StatusCode::kApplicationError:
			return ECommandResponseCode::ApplicationError;
		default:
			return ECommandResponseCode::Unknown;
	}	
}

UCommander::UCommander()
: Component(nullptr)
, EntityQueryCountCommandResult(nullptr)
, EntityQuerySnapshotCommandResult(nullptr)
, SpawnPlayerResponse(nullptr)
, HeartbeatResponse(nullptr)
{
}

UCommander* UCommander::Init(USpatialOsComponent* InComponent, const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView)
{
	Connection = InConnection;
	View = InView;
	Component = InComponent;
		
	SpawnPlayerResponse = NewObject<USpawnPlayerResponse>(this, USpawnPlayerResponse::StaticClass());
	HeartbeatResponse = NewObject<UHeartbeatResponse>(this, UHeartbeatResponse::StaticClass());

	auto LockedView = View.Pin();

	if(LockedView.IsValid())
	{
		Callbacks.Reset(new improbable::unreal::callbacks::FScopedViewCallbacks(View));

		Callbacks->Add(LockedView->OnReserveEntityIdResponse(std::bind(
			&UCommander::OnReserveEntityIdResponseDispatcherCallback, this, std::placeholders::_1)));

		Callbacks->Add(LockedView->OnReserveEntityIdsResponse(std::bind(
			&UCommander::OnReserveEntityIdsResponseDispatcherCallback, this, std::placeholders::_1)));

		Callbacks->Add(LockedView->OnCreateEntityResponse(std::bind(
			&UCommander::OnCreateEntityResponseDispatcherCallback, this, std::placeholders::_1)));

		Callbacks->Add(LockedView->OnDeleteEntityResponse(std::bind(
			&UCommander::OnDeleteEntityResponseDispatcherCallback, this, std::placeholders::_1)));

		Callbacks->Add(LockedView->OnEntityQueryResponse(std::bind(
			&UCommander::OnEntityQueryCommandResponseDispatcherCallback, this, std::placeholders::_1)));

				Callbacks->Add(LockedView->OnCommandResponse<improbable::spawner::Spawner::Commands::SpawnPlayer>(std::bind(
			&UCommander::OnSpawnPlayerCommandResponseDispatcherCallback, this, std::placeholders::_1)));

				Callbacks->Add(LockedView->OnCommandResponse<improbable::player::HeartbeatReceiver::Commands::Heartbeat>(std::bind(
			&UCommander::OnHeartbeatCommandResponseDispatcherCallback, this, std::placeholders::_1)));

			
	}

	return this;
}

void UCommander::BeginDestroy()
{
	Super::BeginDestroy();

	Callbacks.Reset(nullptr);
}

FRequestId UCommander::ReserveEntityId(const FReserveEntityIdResultDelegate& callback, int timeoutMs)
{
	FRequestId WrappedRequestId;
	if (Component != nullptr && Component->GetAuthority() != EAuthority::Authoritative && Component->GetAuthority() != EAuthority::AuthorityLossImminent)
	{
		FSpatialOSCommandResult CommandResult;
		CommandResult.StatusCode = ECommandResponseCode::PermissionDenied;
		CommandResult.ErrorMessage = FString("Tried to reserve an entity id from a component you do not have authority on.");
		callback.ExecuteIfBound(CommandResult, 0);
	}
	else {
		auto LockedConnection = Connection.Pin();

		if(LockedConnection.IsValid())
		{
			auto requestId = LockedConnection->SendReserveEntityIdRequest(timeoutMs);
			RequestIdToReserveEntityIdCallback.Emplace(requestId.Id, callback);
			WrappedRequestId = FRequestId(requestId.Id, true);
		}
	}
	return WrappedRequestId;
}

void UCommander::OnReserveEntityIdResponseDispatcherCallback(const worker::ReserveEntityIdResponseOp& op)
{
	if (RequestIdToReserveEntityIdCallback.Find(op.RequestId.Id) == nullptr)
	{
		return;
	}
	auto callback = RequestIdToReserveEntityIdCallback[op.RequestId.Id];
    FSpatialOSCommandResult CommandResult;
	CommandResult.StatusCode = GetCommandResponseCode(op.StatusCode);
	CommandResult.ErrorMessage = FString(op.Message.c_str());
	CommandResult.RequestId = FRequestId(op.RequestId.Id, true);
	FEntityId EntityId = FEntityId((op.EntityId.empty() ? 0 : *(op.EntityId.data())));
	if (!callback.IsBound())
	{
		UE_LOG(LogTemp, Warning,
			TEXT("OnReserveEntityIdResponse callback is no longer bound!"),
			*GetName())
	}
	callback.ExecuteIfBound(CommandResult, EntityId);
	RequestIdToReserveEntityIdCallback.Remove(op.RequestId.Id);
}

FRequestId UCommander::ReserveEntityIds(int NumEntitiesToReserve, const FReserveEntityIdsResultDelegate& callback, int timeoutMs)
{
	FRequestId WrappedRequestId;
	if (Component != nullptr && Component->GetAuthority() != EAuthority::Authoritative && Component->GetAuthority() != EAuthority::AuthorityLossImminent)
	{
		TArray<FEntityId> EmptyResult;
		FSpatialOSCommandResult CommandResult;
		CommandResult.StatusCode = ECommandResponseCode::PermissionDenied;
		CommandResult.ErrorMessage = FString("Tried to reserve entity ids from a component you do not have authority on.");
		callback.ExecuteIfBound(CommandResult, EmptyResult);
	}
	else 
	{
		auto LockedConnection = Connection.Pin();

		if (LockedConnection.IsValid())
		{
			auto requestId = LockedConnection->SendReserveEntityIdsRequest(NumEntitiesToReserve, timeoutMs);
			RequestIdToReserveEntityIdsCallback.Emplace(requestId.Id, callback);
			WrappedRequestId = FRequestId(requestId.Id, true);
		}
	}
	return WrappedRequestId;
}

void UCommander::OnReserveEntityIdsResponseDispatcherCallback(const worker::ReserveEntityIdsResponseOp& op)
{
	auto callback = RequestIdToReserveEntityIdsCallback.Find(op.RequestId.Id);
	if (callback == nullptr)
	{
		return;
	}

	FSpatialOSCommandResult CommandResult;
	CommandResult.StatusCode = GetCommandResponseCode(op.StatusCode);
	CommandResult.ErrorMessage = FString(op.Message.c_str());
	CommandResult.RequestId = FRequestId(op.RequestId.Id, true);
	if (!(*callback).IsBound())
	{
		UE_LOG(LogTemp, Warning,
			TEXT("OnReserveEntityIdsResponse callback is no longer bound!"),
			*GetName())
	}
	else 
	{
		TArray<FEntityId> ReservedEntityIds;
		if (CommandResult.StatusCode == ECommandResponseCode::Success && !op.FirstEntityId.empty())
		{
			const auto FirstEntityId = *(op.FirstEntityId.data());
			for (auto i = 0; i < op.NumberOfEntityIds; ++i)
			{
				ReservedEntityIds.Emplace(FEntityId(FirstEntityId + i));
			}
		}

		(*callback).ExecuteIfBound(CommandResult, ReservedEntityIds);
	}

	RequestIdToReserveEntityIdsCallback.Remove(op.RequestId.Id);
}

FRequestId UCommander::CreateEntity(UEntityTemplate* entityTemplate, FEntityId entityId, const FCreateEntityResultDelegate& callback, int timeoutMs)
{
	FRequestId WrappedRequestId;
	if (Component != nullptr && Component->GetAuthority() != EAuthority::Authoritative && Component->GetAuthority() != EAuthority::AuthorityLossImminent)
	{
		FSpatialOSCommandResult CommandResult;
		CommandResult.StatusCode = ECommandResponseCode::PermissionDenied;
		CommandResult.ErrorMessage = FString("Tried to create an entity from a component you do not have authority on.");

		callback.ExecuteIfBound(CommandResult, 0);
	}
	else
	{
		auto LockedConnection = Connection.Pin();

		if(LockedConnection.IsValid())
		{
			auto requestId = LockedConnection->SendCreateEntityRequest(entityTemplate->GetUnderlying(), worker::Option<worker::EntityId>(entityId.ToSpatialEntityId()), timeoutMs);
			RequestIdToCreateEntityCallback.Emplace(requestId.Id, callback);
			WrappedRequestId = FRequestId(requestId.Id, true);
		}
	}
	return WrappedRequestId;
}

void UCommander::OnCreateEntityResponseDispatcherCallback(const worker::CreateEntityResponseOp& op)
{
	if (RequestIdToCreateEntityCallback.Find(op.RequestId.Id) == nullptr)
	{
		return;
	}
	auto callback = RequestIdToCreateEntityCallback[op.RequestId.Id];
    FSpatialOSCommandResult CommandResult;
	CommandResult.StatusCode = GetCommandResponseCode(op.StatusCode);
	CommandResult.ErrorMessage = FString(op.Message.c_str());
	CommandResult.RequestId = FRequestId(op.RequestId.Id, true);
	FEntityId EntityId = FEntityId((op.EntityId.empty() ? 0 : *(op.EntityId.data())));
	if (!callback.IsBound())
	{
		UE_LOG(LogTemp, Warning,
			TEXT("OnCreateEntityResponse callback is no longer bound!"),
			*GetName())
	}
	callback.ExecuteIfBound(CommandResult, EntityId);
	RequestIdToCreateEntityCallback.Remove(op.RequestId.Id);
}

FRequestId UCommander::DeleteEntity(FEntityId entityId, const FDeleteEntityResultDelegate& callback, int timeoutMs)
{
	FRequestId WrappedRequestId;
	if (Component != nullptr && Component->GetAuthority() != EAuthority::Authoritative && Component->GetAuthority() != EAuthority::AuthorityLossImminent)
	{
		FSpatialOSCommandResult CommandResult;
		CommandResult.StatusCode = ECommandResponseCode::PermissionDenied;
		CommandResult.ErrorMessage = FString("Tried to delete an entity from a component you do not have authority on.");

		callback.ExecuteIfBound(CommandResult);
	}
	else 
	{
		auto LockedConnection = Connection.Pin();

		if(LockedConnection.IsValid())
		{
			auto requestId = LockedConnection->SendDeleteEntityRequest(entityId.ToSpatialEntityId(), timeoutMs);
			RequestIdToDeleteEntityCallback.Emplace(requestId.Id, callback);
			WrappedRequestId = FRequestId(requestId.Id, true);
		}
	}
	return WrappedRequestId;
}

void UCommander::OnDeleteEntityResponseDispatcherCallback(const worker::DeleteEntityResponseOp& op)
{
	if (RequestIdToDeleteEntityCallback.Find(op.RequestId.Id) == nullptr)
	{
		return;
	}
	auto callback = RequestIdToDeleteEntityCallback[op.RequestId.Id];
    FSpatialOSCommandResult CommandResult;
	CommandResult.StatusCode = GetCommandResponseCode(op.StatusCode);
	CommandResult.ErrorMessage = FString(op.Message.c_str());
	CommandResult.RequestId = FRequestId(op.RequestId.Id, true);
	if (!callback.IsBound())
	{
		UE_LOG(LogTemp, Warning,
			TEXT("OnDeleteEntityResponse callback is no longer bound!"),
			*GetName())
	}
	callback.ExecuteIfBound(CommandResult);
	RequestIdToDeleteEntityCallback.Remove(op.RequestId.Id);
}

FRequestId UCommander::EntityQueryCountRequest(UEntityQueryConstraint* EntityQuery, const FEntityQueryCountResultDelegate& callback, int timeoutMs)
{
	FRequestId WrappedRequestId;
	auto lockedConnection = Connection.Pin();
	if (lockedConnection.IsValid())
	{
		worker::query::EntityQuery query{ *(EntityQuery->Underlying), worker::query::CountResultType{} };
		auto queryId = lockedConnection->SendEntityQueryRequest(query, timeoutMs);
		RequestIdToEntityQueryCountCommandCallback.Emplace(queryId.Id, callback);
		WrappedRequestId = FRequestId(queryId.Id, true);
	}
	return WrappedRequestId;
}

FRequestId UCommander::EntityQuerySnapshotRequest(UEntityQueryConstraint* EntityQuery, const TArray<FComponentId>& ComponentIds, const FEntityQuerySnapshotResultDelegate& callback, int timeoutMs)
{
	FRequestId WrappedRequestId;
	auto lockedConnection = Connection.Pin();
	if (lockedConnection.IsValid())
	{
		worker::query::SnapshotResultType snapshotType{};
		if (ComponentIds.Num() > 0)
		{
			worker::List<worker::ComponentId> componentIdList;
			for (const FComponentId& id : ComponentIds)
			{
				componentIdList.emplace_back(id.ToSpatialComponentId());
			}
			snapshotType.ComponentIds = componentIdList;
		}

		worker::query::EntityQuery query{ *(EntityQuery->Underlying), snapshotType };
		auto queryId = lockedConnection->SendEntityQueryRequest(query, timeoutMs);
		RequestIdToEntityQuerySnapshotCommandCallback.Emplace(queryId.Id, callback);
		WrappedRequestId = FRequestId(queryId.Id, true);
	}
	return WrappedRequestId;
}

void UCommander::OnEntityQueryCommandResponseDispatcherCallback(const worker::EntityQueryResponseOp& op)
{
	auto countCallback = RequestIdToEntityQueryCountCommandCallback.Find(op.RequestId.Id);
	auto snapshotCallback = RequestIdToEntityQuerySnapshotCommandCallback.Find(op.RequestId.Id);
	if (countCallback != nullptr)
	{
		if (EntityQueryCountCommandResult == nullptr)
		{
			EntityQueryCountCommandResult = NewObject<UEntityQueryCountCommandResult>(this, UEntityQueryCountCommandResult::StaticClass());
		}
		EntityQueryCountCommandResult->Init(op);

		if (!(*countCallback).IsBound())
		{
			UE_LOG(LogTemp, Warning,
				TEXT("OnEntityQueryCommandResponse callback is no longer bound!"),
				*GetName())
		}
		(*countCallback).ExecuteIfBound(EntityQueryCountCommandResult);
		RequestIdToEntityQueryCountCommandCallback.Remove(op.RequestId.Id);
	}
	else if (snapshotCallback != nullptr)
	{
		if (EntityQuerySnapshotCommandResult == nullptr)
		{
			EntityQuerySnapshotCommandResult = NewObject<UEntityQuerySnapshotCommandResult>(this, UEntityQuerySnapshotCommandResult::StaticClass());
		}
		EntityQuerySnapshotCommandResult->Init(op);

		if (!(*snapshotCallback).IsBound())
		{
			UE_LOG(LogTemp, Warning,
				TEXT("OnEntityQueryCommandResponse callback is no longer bound!"),
				*GetName())
		}
		(*snapshotCallback).ExecuteIfBound(EntityQuerySnapshotCommandResult);
		RequestIdToEntityQuerySnapshotCommandCallback.Remove(op.RequestId.Id);
	}
}

FRequestId UCommander::SpawnPlayer(FEntityId entityId, USpawnPlayerRequest* request, const FSpawnPlayerCommandResultDelegate& callback, int timeoutMs, ECommandDelivery commandDelivery)
{	
	FRequestId WrappedRequestId;
	if (Component != nullptr && Component->GetAuthority() != EAuthority::Authoritative && Component->GetAuthority() != EAuthority::AuthorityLossImminent)
	{
		FSpatialOSCommandResult CommandResult;
		CommandResult.StatusCode = ECommandResponseCode::PermissionDenied;
		CommandResult.ErrorMessage = FString("Error sending command: Tried to send a SpawnPlayer command from a component which the worker does not have authority on.");
				
		callback.ExecuteIfBound(CommandResult, nullptr);
	}
	else
	{
		auto LockedConnection = Connection.Pin();

		if(LockedConnection.IsValid())
		{
			worker::CommandParameters parameters;
			parameters.AllowShortCircuit = (commandDelivery == ECommandDelivery::SHORT_CIRCUIT);
			auto underlyingRequest = request->GetUnderlying();
			auto requestId = LockedConnection->SendCommandRequest<improbable::spawner::Spawner::Commands::SpawnPlayer>(entityId.ToSpatialEntityId(), underlyingRequest, worker::Option<std::uint32_t>(timeoutMs), parameters);
			RequestIdToSpawnPlayerCommandCallback.Emplace(requestId.Id, callback);
			WrappedRequestId = FRequestId(requestId.Id, true);
		}
	}
	return WrappedRequestId;
}

void UCommander::OnSpawnPlayerCommandResponseDispatcherCallback(const worker::CommandResponseOp<improbable::spawner::Spawner::Commands::SpawnPlayer>& op)
{
	check(SpawnPlayerResponse);
	auto callback = RequestIdToSpawnPlayerCommandCallback.Find(op.RequestId.Id);
	if (callback == nullptr)
	{
		return;
	}

	if (!callback->IsBound())
	{
		UE_LOG(LogTemp, Warning,
			TEXT("OnSpawnPlayerCommandResponse callback is no longer bound!"),
			*GetName())

		RequestIdToSpawnPlayerCommandCallback.Remove(op.RequestId.Id);
		return;
	}

	FSpatialOSCommandResult CommandResult;
	CommandResult.StatusCode = GetCommandResponseCode(op.StatusCode);
	CommandResult.ErrorMessage = FString(op.Message.c_str());
	CommandResult.RequestId = FRequestId(op.RequestId.Id, true);

	if (CommandResult.StatusCode == ECommandResponseCode::Success && !op.Response.empty())
	{
		SpawnPlayerResponse->Init(*(op.Response.data()));
	}

	callback->ExecuteIfBound(CommandResult, CommandResult.StatusCode == ECommandResponseCode::Success ? SpawnPlayerResponse : nullptr);
	RequestIdToSpawnPlayerCommandCallback.Remove(op.RequestId.Id);
}

FRequestId UCommander::Heartbeat(FEntityId entityId, UHeartbeatRequest* request, const FHeartbeatCommandResultDelegate& callback, int timeoutMs, ECommandDelivery commandDelivery)
{	
	FRequestId WrappedRequestId;
	if (Component != nullptr && Component->GetAuthority() != EAuthority::Authoritative && Component->GetAuthority() != EAuthority::AuthorityLossImminent)
	{
		FSpatialOSCommandResult CommandResult;
		CommandResult.StatusCode = ECommandResponseCode::PermissionDenied;
		CommandResult.ErrorMessage = FString("Error sending command: Tried to send a Heartbeat command from a component which the worker does not have authority on.");
				
		callback.ExecuteIfBound(CommandResult, nullptr);
	}
	else
	{
		auto LockedConnection = Connection.Pin();

		if(LockedConnection.IsValid())
		{
			worker::CommandParameters parameters;
			parameters.AllowShortCircuit = (commandDelivery == ECommandDelivery::SHORT_CIRCUIT);
			auto underlyingRequest = request->GetUnderlying();
			auto requestId = LockedConnection->SendCommandRequest<improbable::player::HeartbeatReceiver::Commands::Heartbeat>(entityId.ToSpatialEntityId(), underlyingRequest, worker::Option<std::uint32_t>(timeoutMs), parameters);
			RequestIdToHeartbeatCommandCallback.Emplace(requestId.Id, callback);
			WrappedRequestId = FRequestId(requestId.Id, true);
		}
	}
	return WrappedRequestId;
}

void UCommander::OnHeartbeatCommandResponseDispatcherCallback(const worker::CommandResponseOp<improbable::player::HeartbeatReceiver::Commands::Heartbeat>& op)
{
	check(HeartbeatResponse);
	auto callback = RequestIdToHeartbeatCommandCallback.Find(op.RequestId.Id);
	if (callback == nullptr)
	{
		return;
	}

	if (!callback->IsBound())
	{
		UE_LOG(LogTemp, Warning,
			TEXT("OnHeartbeatCommandResponse callback is no longer bound!"),
			*GetName())

		RequestIdToHeartbeatCommandCallback.Remove(op.RequestId.Id);
		return;
	}

	FSpatialOSCommandResult CommandResult;
	CommandResult.StatusCode = GetCommandResponseCode(op.StatusCode);
	CommandResult.ErrorMessage = FString(op.Message.c_str());
	CommandResult.RequestId = FRequestId(op.RequestId.Id, true);

	if (CommandResult.StatusCode == ECommandResponseCode::Success && !op.Response.empty())
	{
		HeartbeatResponse->Init(*(op.Response.data()));
	}

	callback->ExecuteIfBound(CommandResult, CommandResult.StatusCode == ECommandResponseCode::Success ? HeartbeatResponse : nullptr);
	RequestIdToHeartbeatCommandCallback.Remove(op.RequestId.Id);
}

