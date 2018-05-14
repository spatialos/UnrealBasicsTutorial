// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "SpatialOSViewTypes.h"
#include "SpatialOSWorkerTypes.h"
#include "EntityPipelineBlock.h"
#include "ScopedViewCallbacks.h"
#include "SpawnerAddComponentOp.h"
#include "HeartbeatReceiverAddComponentOp.h"
#include "HeartbeatSenderAddComponentOp.h"
#include "EntityAclAddComponentOp.h"
#include "MetadataAddComponentOp.h"
#include "PositionAddComponentOp.h"
#include "PersistenceAddComponentOp.h"
#include "EntityPipeline.generated.h"

UCLASS()
class SPATIALOS_API UEntityPipeline : public UObject
{
	GENERATED_BODY()

public:
	UEntityPipeline();

	/**
	* Initialise the UEntityPipeline. Calling Init() more than once results in an error.
	*/
	void Init(const TWeakPtr<SpatialOSView>& InView, UCallbackDispatcher* InCallbackDispatcher);

	/**
	* Deregister all callbacks. Init() may be called again after this method is called.
	*/
	void DeregisterAllCallbacks();

	void AddBlock(UEntityPipelineBlock* NewBlock);
	void ProcessOps(const TWeakPtr<SpatialOSView>& InView, const TWeakPtr<SpatialOSConnection>& InConnection, UWorld* World);

	void OnAddEntity(const worker::AddEntityOp& Op) { FirstBlock->AddEntity(Op); }
	void OnRemoveEntity(const worker::RemoveEntityOp& Op) { FirstBlock->RemoveEntity(Op); }
	void OnRemoveComponent(const worker::ComponentId ComponentId, const worker::RemoveComponentOp& Op) { FirstBlock->RemoveComponent(ComponentId, Op); }
	void OnAuthorityChange(const worker::ComponentId ComponentId, const worker::AuthorityChangeOp& Op) { FirstBlock->ChangeAuthority(ComponentId, Op); }

	void AddSpawnerComponentOp(const worker::AddComponentOp<improbable::spawner::Spawner>& Op);
	void RemoveSpawnerComponentOp(const worker::RemoveComponentOp& Op);
	void AddHeartbeatReceiverComponentOp(const worker::AddComponentOp<improbable::player::HeartbeatReceiver>& Op);
	void RemoveHeartbeatReceiverComponentOp(const worker::RemoveComponentOp& Op);
	void AddHeartbeatSenderComponentOp(const worker::AddComponentOp<improbable::player::HeartbeatSender>& Op);
	void RemoveHeartbeatSenderComponentOp(const worker::RemoveComponentOp& Op);
	void AddEntityAclComponentOp(const worker::AddComponentOp<improbable::EntityAcl>& Op);
	void RemoveEntityAclComponentOp(const worker::RemoveComponentOp& Op);
	void AddMetadataComponentOp(const worker::AddComponentOp<improbable::Metadata>& Op);
	void RemoveMetadataComponentOp(const worker::RemoveComponentOp& Op);
	void AddPositionComponentOp(const worker::AddComponentOp<improbable::Position>& Op);
	void RemovePositionComponentOp(const worker::RemoveComponentOp& Op);
	void AddPersistenceComponentOp(const worker::AddComponentOp<improbable::Persistence>& Op);
	void RemovePersistenceComponentOp(const worker::RemoveComponentOp& Op);

private:
	UPROPERTY()
	UEntityPipelineBlock* FirstBlock;
	UPROPERTY()
	UEntityPipelineBlock* LastBlock;
	UPROPERTY()
	UCallbackDispatcher* CallbackDispatcher;

	bool bInitialised;
	improbable::unreal::callbacks::FScopedViewCallbacks Callbacks;
};
