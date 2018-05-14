// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScopedViewCallbacks.h"
#include "improbable/spawner/spawner.h"
#include "improbable/player/heartbeat.h"
#include "improbable/standard_library.h"
#include "EntityId.h"
#include "RequestId.h"
#include "ComponentId.h"
#include "CommanderTypes.h"
#include "EntityTemplate.h"
#include "EntityQueryConstraints.h"
#include "EntityQueryCommandResult.h"
#include "SpatialOSCommandResult.h"
#include "SpatialOsComponent.h"
#include "SpatialOSViewTypes.h"
#include "SpatialOSWorkerTypes.h"

#include "Commander.generated.h"

class USpatialOsComponent;
class USpawnPlayerResponse;
class UHeartbeatResponse;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FReserveEntityIdResultDelegate, const FSpatialOSCommandResult&, result, FEntityId, reservedEntityId);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FReserveEntityIdsResultDelegate, const FSpatialOSCommandResult&, result, const TArray<FEntityId>&, reservedEntityIds);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FCreateEntityResultDelegate, const FSpatialOSCommandResult&, result, FEntityId, createdEntityId);
DECLARE_DYNAMIC_DELEGATE_OneParam(FDeleteEntityResultDelegate, const FSpatialOSCommandResult&, result);
DECLARE_DYNAMIC_DELEGATE_OneParam(FEntityQueryCountResultDelegate, UEntityQueryCountCommandResult*, result);
DECLARE_DYNAMIC_DELEGATE_OneParam(FEntityQuerySnapshotResultDelegate, UEntityQuerySnapshotCommandResult*, result);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FSpawnPlayerCommandResultDelegate, const FSpatialOSCommandResult&, result, USpawnPlayerResponse*, response);	
DECLARE_DYNAMIC_DELEGATE_TwoParams(FHeartbeatCommandResultDelegate, const FSpatialOSCommandResult&, result, UHeartbeatResponse*, response);	

/**
*
*/
UCLASS(BlueprintType)
class SPATIALOS_API UCommander : public UObject
{
	GENERATED_BODY()

public:
	UCommander();

	UCommander* Init(USpatialOsComponent* component, const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView);

	virtual void BeginDestroy() override;
		
	UFUNCTION(BlueprintCallable, Category = "SpatialOS Commands")
	FRequestId ReserveEntityId(const FReserveEntityIdResultDelegate& callback, int timeoutMs);

	UFUNCTION(BlueprintCallable, Category = "SpatialOS Commands")
	FRequestId ReserveEntityIds(int NumEntitiesToReserve, const FReserveEntityIdsResultDelegate& callback, int timeoutMs);
	    
	UFUNCTION(BlueprintCallable, Category = "SpatialOS Commands")
	FRequestId CreateEntity(UEntityTemplate* entityTemplate, FEntityId entityId, const FCreateEntityResultDelegate& callback, int timeoutMs);
	    
	UFUNCTION(BlueprintCallable, Category = "SpatialOS Commands")
	FRequestId DeleteEntity(FEntityId entityId, const FDeleteEntityResultDelegate& callback, int timeoutMs);

	UFUNCTION(BlueprintCallable, Category = "Commands") 
	FRequestId EntityQueryCountRequest(UEntityQueryConstraint* EntityQuery, const FEntityQueryCountResultDelegate& callback, int timeoutMs);

	UFUNCTION(BlueprintCallable, Category = "Commands", meta = (AutoCreateRefTerm = "ComponentIds"))
	FRequestId EntityQuerySnapshotRequest(UEntityQueryConstraint* EntityQuery, const TArray<FComponentId>& ComponentIds, const FEntityQuerySnapshotResultDelegate& callback, int timeoutMs);

	UFUNCTION(BlueprintCallable, Category = "SpatialOS Commands")
	FRequestId SpawnPlayer(FEntityId entityId, USpawnPlayerRequest* request, const FSpawnPlayerCommandResultDelegate& callback, int timeoutMs, ECommandDelivery commandDelivery = ECommandDelivery::ROUNDTRIP);

	UFUNCTION(BlueprintCallable, Category = "SpatialOS Commands")
	FRequestId Heartbeat(FEntityId entityId, UHeartbeatRequest* request, const FHeartbeatCommandResultDelegate& callback, int timeoutMs, ECommandDelivery commandDelivery = ECommandDelivery::ROUNDTRIP);

	static ECommandResponseCode GetCommandResponseCode(const worker::StatusCode UnderlyingStatusCode);

private:
	TWeakPtr<SpatialOSConnection> Connection;
	TWeakPtr<SpatialOSView> View;

	UPROPERTY()
	USpatialOsComponent* Component;

	UPROPERTY()
	UEntityQueryCountCommandResult* EntityQueryCountCommandResult;

	UPROPERTY()
	UEntityQuerySnapshotCommandResult* EntityQuerySnapshotCommandResult;

	UPROPERTY()
	USpawnPlayerResponse* SpawnPlayerResponse;
	UPROPERTY()
	UHeartbeatResponse* HeartbeatResponse;

	TUniquePtr<improbable::unreal::callbacks::FScopedViewCallbacks> Callbacks;

	TMap<uint32_t, const FReserveEntityIdResultDelegate> RequestIdToReserveEntityIdCallback;
	void OnReserveEntityIdResponseDispatcherCallback(const worker::ReserveEntityIdResponseOp& op);

	TMap<uint32_t, const FReserveEntityIdsResultDelegate> RequestIdToReserveEntityIdsCallback;
	void OnReserveEntityIdsResponseDispatcherCallback(const worker::ReserveEntityIdsResponseOp& op);

    TMap<uint32_t, const FCreateEntityResultDelegate> RequestIdToCreateEntityCallback;
	void OnCreateEntityResponseDispatcherCallback(const worker::CreateEntityResponseOp& op);

    TMap<uint32_t, const FDeleteEntityResultDelegate> RequestIdToDeleteEntityCallback;
	void OnDeleteEntityResponseDispatcherCallback(const worker::DeleteEntityResponseOp& op);

	TMap<uint32_t, FEntityQueryCountResultDelegate> RequestIdToEntityQueryCountCommandCallback;
	TMap<uint32_t, FEntityQuerySnapshotResultDelegate> RequestIdToEntityQuerySnapshotCommandCallback;
	void OnEntityQueryCommandResponseDispatcherCallback(const worker::EntityQueryResponseOp& op);

	TMap<uint32_t, const FSpawnPlayerCommandResultDelegate> RequestIdToSpawnPlayerCommandCallback;
	void OnSpawnPlayerCommandResponseDispatcherCallback(const worker::CommandResponseOp<improbable::spawner::Spawner::Commands::SpawnPlayer>& op);

	TMap<uint32_t, const FHeartbeatCommandResultDelegate> RequestIdToHeartbeatCommandCallback;
	void OnHeartbeatCommandResponseDispatcherCallback(const worker::CommandResponseOp<improbable::player::HeartbeatReceiver::Commands::Heartbeat>& op);

};
