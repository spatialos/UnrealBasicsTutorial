// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "EntityPipeline.h"
#include "EntityPipelineBlock.h"
#include "CoreMinimal.h"

#include "SpatialOSViewTypes.h"
#include "SpatialOSWorkerTypes.h"
#include "CallbackDispatcher.h"
#include "SpawnerAddComponentOp.h"
#include "HeartbeatReceiverAddComponentOp.h"
#include "HeartbeatSenderAddComponentOp.h"
#include "EntityAclAddComponentOp.h"
#include "MetadataAddComponentOp.h"
#include "PositionAddComponentOp.h"
#include "PersistenceAddComponentOp.h"

/**
*
*/

DECLARE_LOG_CATEGORY_EXTERN(LogEntityPipeline, Log, All);
DEFINE_LOG_CATEGORY(LogEntityPipeline);

UEntityPipeline::UEntityPipeline()
: FirstBlock(nullptr)
, LastBlock(nullptr)
, CallbackDispatcher(nullptr)
, bInitialised(false)
{
}

void UEntityPipeline::Init(const TWeakPtr<SpatialOSView>& InView, UCallbackDispatcher* InCallbackDispatcher)
{
	checkf(!bInitialised, TEXT("Attempting to call Init more than once!"));
	checkf(FirstBlock, TEXT("Trying to bind callbacks but no blocks have been added!"));

	Callbacks.Init(InView);
	CallbackDispatcher = InCallbackDispatcher;
	CallbackDispatcher->OnAuthorityChangeOpReceived.AddUObject(this, &UEntityPipeline::OnAuthorityChange);

	auto LockedView = InView.Pin();
	if (LockedView.IsValid())
	{
		Callbacks.Add(LockedView->OnAddEntity(
			std::bind(&UEntityPipeline::OnAddEntity, this, std::placeholders::_1)));

		Callbacks.Add(LockedView->OnRemoveEntity(
			std::bind(&UEntityPipeline::OnRemoveEntity, this, std::placeholders::_1)));

		Callbacks.Add(LockedView->OnAddComponent<improbable::spawner::Spawner>(
			std::bind(&UEntityPipeline::AddSpawnerComponentOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAddComponent<improbable::player::HeartbeatReceiver>(
			std::bind(&UEntityPipeline::AddHeartbeatReceiverComponentOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAddComponent<improbable::player::HeartbeatSender>(
			std::bind(&UEntityPipeline::AddHeartbeatSenderComponentOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAddComponent<improbable::EntityAcl>(
			std::bind(&UEntityPipeline::AddEntityAclComponentOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAddComponent<improbable::Metadata>(
			std::bind(&UEntityPipeline::AddMetadataComponentOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAddComponent<improbable::Position>(
			std::bind(&UEntityPipeline::AddPositionComponentOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAddComponent<improbable::Persistence>(
			std::bind(&UEntityPipeline::AddPersistenceComponentOp, this, std::placeholders::_1)));

		Callbacks.Add(LockedView->OnRemoveComponent<improbable::spawner::Spawner>(
			std::bind(&UEntityPipeline::RemoveSpawnerComponentOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnRemoveComponent<improbable::player::HeartbeatReceiver>(
			std::bind(&UEntityPipeline::RemoveHeartbeatReceiverComponentOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnRemoveComponent<improbable::player::HeartbeatSender>(
			std::bind(&UEntityPipeline::RemoveHeartbeatSenderComponentOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnRemoveComponent<improbable::EntityAcl>(
			std::bind(&UEntityPipeline::RemoveEntityAclComponentOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnRemoveComponent<improbable::Metadata>(
			std::bind(&UEntityPipeline::RemoveMetadataComponentOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnRemoveComponent<improbable::Position>(
			std::bind(&UEntityPipeline::RemovePositionComponentOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnRemoveComponent<improbable::Persistence>(
			std::bind(&UEntityPipeline::RemovePersistenceComponentOp, this, std::placeholders::_1)));

	}
	bInitialised = true;
}

void UEntityPipeline::DeregisterAllCallbacks()
{
	if (CallbackDispatcher != nullptr)
	{
		CallbackDispatcher->Reset();
		CallbackDispatcher = nullptr;
	}
	Callbacks.Reset();
	bInitialised = false;
}

void UEntityPipeline::AddBlock(UEntityPipelineBlock* NewBlock)
{
    checkf(!bInitialised, TEXT("Cannot add blocks after the pipeline has started"));

    if(FirstBlock == nullptr)
	{
		FirstBlock = NewBlock;
	}
	if(LastBlock != nullptr)
	{
		LastBlock->NextBlock = NewBlock;
	}
	LastBlock = NewBlock;
}

void UEntityPipeline::ProcessOps(const TWeakPtr<SpatialOSView>& InView, const TWeakPtr<SpatialOSConnection>& InConnection, UWorld* World)
{
	auto Block = FirstBlock;

	while (Block != nullptr)
	{
		Block->ProcessOps(InView, InConnection, World, CallbackDispatcher);
		Block = Block->NextBlock;
	}
}

void UEntityPipeline::AddSpawnerComponentOp(const worker::AddComponentOp<improbable::spawner::Spawner>& Op) {
	USpawnerAddComponentOp* NewOp = NewObject<USpawnerAddComponentOp>();
	if (NewOp)
	{
		NewOp->Data = Op.Data;
		NewOp->ComponentId = improbable::spawner::Spawner::ComponentId;
		NewOp->EntityId = Op.EntityId;

		FirstBlock->AddComponent(NewOp);
	}
}

void UEntityPipeline::RemoveSpawnerComponentOp(const worker::RemoveComponentOp& Op) {
	const worker::ComponentId ComponentId = improbable::spawner::Spawner::ComponentId;
	FirstBlock->RemoveComponent(ComponentId, Op);
}
void UEntityPipeline::AddHeartbeatReceiverComponentOp(const worker::AddComponentOp<improbable::player::HeartbeatReceiver>& Op) {
	UHeartbeatReceiverAddComponentOp* NewOp = NewObject<UHeartbeatReceiverAddComponentOp>();
	if (NewOp)
	{
		NewOp->Data = Op.Data;
		NewOp->ComponentId = improbable::player::HeartbeatReceiver::ComponentId;
		NewOp->EntityId = Op.EntityId;

		FirstBlock->AddComponent(NewOp);
	}
}

void UEntityPipeline::RemoveHeartbeatReceiverComponentOp(const worker::RemoveComponentOp& Op) {
	const worker::ComponentId ComponentId = improbable::player::HeartbeatReceiver::ComponentId;
	FirstBlock->RemoveComponent(ComponentId, Op);
}
void UEntityPipeline::AddHeartbeatSenderComponentOp(const worker::AddComponentOp<improbable::player::HeartbeatSender>& Op) {
	UHeartbeatSenderAddComponentOp* NewOp = NewObject<UHeartbeatSenderAddComponentOp>();
	if (NewOp)
	{
		NewOp->Data = Op.Data;
		NewOp->ComponentId = improbable::player::HeartbeatSender::ComponentId;
		NewOp->EntityId = Op.EntityId;

		FirstBlock->AddComponent(NewOp);
	}
}

void UEntityPipeline::RemoveHeartbeatSenderComponentOp(const worker::RemoveComponentOp& Op) {
	const worker::ComponentId ComponentId = improbable::player::HeartbeatSender::ComponentId;
	FirstBlock->RemoveComponent(ComponentId, Op);
}
void UEntityPipeline::AddEntityAclComponentOp(const worker::AddComponentOp<improbable::EntityAcl>& Op) {
	UEntityAclAddComponentOp* NewOp = NewObject<UEntityAclAddComponentOp>();
	if (NewOp)
	{
		NewOp->Data = Op.Data;
		NewOp->ComponentId = improbable::EntityAcl::ComponentId;
		NewOp->EntityId = Op.EntityId;

		FirstBlock->AddComponent(NewOp);
	}
}

void UEntityPipeline::RemoveEntityAclComponentOp(const worker::RemoveComponentOp& Op) {
	const worker::ComponentId ComponentId = improbable::EntityAcl::ComponentId;
	FirstBlock->RemoveComponent(ComponentId, Op);
}
void UEntityPipeline::AddMetadataComponentOp(const worker::AddComponentOp<improbable::Metadata>& Op) {
	UMetadataAddComponentOp* NewOp = NewObject<UMetadataAddComponentOp>();
	if (NewOp)
	{
		NewOp->Data = Op.Data;
		NewOp->ComponentId = improbable::Metadata::ComponentId;
		NewOp->EntityId = Op.EntityId;

		FirstBlock->AddComponent(NewOp);
	}
}

void UEntityPipeline::RemoveMetadataComponentOp(const worker::RemoveComponentOp& Op) {
	const worker::ComponentId ComponentId = improbable::Metadata::ComponentId;
	FirstBlock->RemoveComponent(ComponentId, Op);
}
void UEntityPipeline::AddPositionComponentOp(const worker::AddComponentOp<improbable::Position>& Op) {
	UPositionAddComponentOp* NewOp = NewObject<UPositionAddComponentOp>();
	if (NewOp)
	{
		NewOp->Data = Op.Data;
		NewOp->ComponentId = improbable::Position::ComponentId;
		NewOp->EntityId = Op.EntityId;

		FirstBlock->AddComponent(NewOp);
	}
}

void UEntityPipeline::RemovePositionComponentOp(const worker::RemoveComponentOp& Op) {
	const worker::ComponentId ComponentId = improbable::Position::ComponentId;
	FirstBlock->RemoveComponent(ComponentId, Op);
}
void UEntityPipeline::AddPersistenceComponentOp(const worker::AddComponentOp<improbable::Persistence>& Op) {
	UPersistenceAddComponentOp* NewOp = NewObject<UPersistenceAddComponentOp>();
	if (NewOp)
	{
		NewOp->Data = Op.Data;
		NewOp->ComponentId = improbable::Persistence::ComponentId;
		NewOp->EntityId = Op.EntityId;

		FirstBlock->AddComponent(NewOp);
	}
}

void UEntityPipeline::RemovePersistenceComponentOp(const worker::RemoveComponentOp& Op) {
	const worker::ComponentId ComponentId = improbable::Persistence::ComponentId;
	FirstBlock->RemoveComponent(ComponentId, Op);
}
