// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "UObject/Class.h"
#include "SpatialOSViewTypes.h"
#include "SpatialOSWorkerTypes.h"
#include "ComponentIdentifier.h"
#include "ComponentUpdateQueue.h"
#include "improbable/spawner/spawner.h"
#include "improbable/player/heartbeat.h"
#include "improbable/standard_library.h"
#include "ScopedViewCallbacks.h"
#include "SpatialOS.h"
#include "CallbackDispatcher.generated.h"

class UComponentUpdateOpWrapperBase;

DECLARE_EVENT_TwoParams( UCallbackDispatcher, FAuthorityChangeOpReceivedEvent, worker::ComponentId, const worker::AuthorityChangeOp&);

UCLASS()
class SPATIALOS_API UCallbackDispatcher : public UObject
{
	GENERATED_BODY()

public:
	UCallbackDispatcher();

	/**
	* Initialise the UCallbackDispatcher. Calling Init() more than once results in an error.
	*/
	void Init(const TWeakPtr<SpatialOSView>& InView);

	/**
	* Reset the UCallbackDispatcher to its initial state. Init() may be called again after this method is called.
	*/
	void Reset();

	void AddComponentUpdateCallback(worker::EntityId EntityId, worker::ComponentId ComponentId, TFunction<void(UComponentUpdateOpWrapperBase&)> Callback);
	void AddAuthorityChangeCallback(worker::EntityId EntityId, worker::ComponentId ComponentId, TFunction<void(const worker::AuthorityChangeOp&)> Callback);

	void RemoveComponentUpdateCallback(worker::EntityId EntityId, worker::ComponentId ComponentId);
	void RemoveAuthorityChangeCallback(worker::EntityId EntityId, worker::ComponentId ComponentId);

	FAuthorityChangeOpReceivedEvent OnAuthorityChangeOpReceived;

	void OnSpawnerComponentUpdateOp(const worker::ComponentUpdateOp<improbable::spawner::Spawner>& Op);
	void OnSpawnerAuthorityChangeOp(const worker::AuthorityChangeOp& Op);

	void OnHeartbeatReceiverComponentUpdateOp(const worker::ComponentUpdateOp<improbable::player::HeartbeatReceiver>& Op);
	void OnHeartbeatReceiverAuthorityChangeOp(const worker::AuthorityChangeOp& Op);

	void OnHeartbeatSenderComponentUpdateOp(const worker::ComponentUpdateOp<improbable::player::HeartbeatSender>& Op);
	void OnHeartbeatSenderAuthorityChangeOp(const worker::AuthorityChangeOp& Op);

	void OnEntityAclComponentUpdateOp(const worker::ComponentUpdateOp<improbable::EntityAcl>& Op);
	void OnEntityAclAuthorityChangeOp(const worker::AuthorityChangeOp& Op);

	void OnMetadataComponentUpdateOp(const worker::ComponentUpdateOp<improbable::Metadata>& Op);
	void OnMetadataAuthorityChangeOp(const worker::AuthorityChangeOp& Op);

	void OnPositionComponentUpdateOp(const worker::ComponentUpdateOp<improbable::Position>& Op);
	void OnPositionAuthorityChangeOp(const worker::AuthorityChangeOp& Op);

	void OnPersistenceComponentUpdateOp(const worker::ComponentUpdateOp<improbable::Persistence>& Op);
	void OnPersistenceAuthorityChangeOp(const worker::AuthorityChangeOp& Op);


private:
	TMap<FComponentIdentifier, TFunction<void(UComponentUpdateOpWrapperBase&)>> ComponentUpdateCallbacks;
	TMap<FComponentIdentifier, TFunction<void(const worker::AuthorityChangeOp&)>> AuthorityChangeCallbacks;
	
	UPROPERTY()
	TMap<FComponentIdentifier, FComponentUpdateQueue> QueuedUpdates;
	
	void HandleUpdate(UComponentUpdateOpWrapperBase* Update);
	void EnqueueUpdate(const FComponentIdentifier& Id, UComponentUpdateOpWrapperBase* Update);
	void DispatchQueuedUpdates(const FComponentIdentifier& Id);

	improbable::unreal::callbacks::FScopedViewCallbacks Callbacks;
	bool bInitialised;
};