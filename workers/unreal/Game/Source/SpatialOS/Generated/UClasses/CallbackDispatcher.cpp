// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 


#include "CallbackDispatcher.h"
#include "ComponentUpdateOpWrapperBase.h"
#include "SpawnerComponentUpdate.h"
#include "HeartbeatReceiverComponentUpdate.h"
#include "HeartbeatSenderComponentUpdate.h"
#include "EntityAclComponentUpdate.h"
#include "MetadataComponentUpdate.h"
#include "PositionComponentUpdate.h"
#include "PersistenceComponentUpdate.h"
#include "ScopedViewCallbacks.h"
#include "SpatialOSViewTypes.h"


DECLARE_LOG_CATEGORY_EXTERN(LogCallbackDispatcher, Log, All);
DEFINE_LOG_CATEGORY(LogCallbackDispatcher);

UCallbackDispatcher::UCallbackDispatcher() : bInitialised(false)
{
}

void UCallbackDispatcher::Init(const TWeakPtr<SpatialOSView>& InView)
{
	checkf(!bInitialised, TEXT("Attempting to call Init more than once!"));
	Callbacks.Init(InView);

	auto LockedView = InView.Pin();
	if(LockedView.IsValid())
	{
		Callbacks.Add(LockedView->OnComponentUpdate<improbable::spawner::Spawner>(std::bind(
			&UCallbackDispatcher::OnSpawnerComponentUpdateOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAuthorityChange<improbable::spawner::Spawner>(std::bind(
			&UCallbackDispatcher::OnSpawnerAuthorityChangeOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnComponentUpdate<improbable::player::HeartbeatReceiver>(std::bind(
			&UCallbackDispatcher::OnHeartbeatReceiverComponentUpdateOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAuthorityChange<improbable::player::HeartbeatReceiver>(std::bind(
			&UCallbackDispatcher::OnHeartbeatReceiverAuthorityChangeOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnComponentUpdate<improbable::player::HeartbeatSender>(std::bind(
			&UCallbackDispatcher::OnHeartbeatSenderComponentUpdateOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAuthorityChange<improbable::player::HeartbeatSender>(std::bind(
			&UCallbackDispatcher::OnHeartbeatSenderAuthorityChangeOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnComponentUpdate<improbable::EntityAcl>(std::bind(
			&UCallbackDispatcher::OnEntityAclComponentUpdateOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAuthorityChange<improbable::EntityAcl>(std::bind(
			&UCallbackDispatcher::OnEntityAclAuthorityChangeOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnComponentUpdate<improbable::Metadata>(std::bind(
			&UCallbackDispatcher::OnMetadataComponentUpdateOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAuthorityChange<improbable::Metadata>(std::bind(
			&UCallbackDispatcher::OnMetadataAuthorityChangeOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnComponentUpdate<improbable::Position>(std::bind(
			&UCallbackDispatcher::OnPositionComponentUpdateOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAuthorityChange<improbable::Position>(std::bind(
			&UCallbackDispatcher::OnPositionAuthorityChangeOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnComponentUpdate<improbable::Persistence>(std::bind(
			&UCallbackDispatcher::OnPersistenceComponentUpdateOp, this, std::placeholders::_1)));
		Callbacks.Add(LockedView->OnAuthorityChange<improbable::Persistence>(std::bind(
			&UCallbackDispatcher::OnPersistenceAuthorityChangeOp, this, std::placeholders::_1)));
	}
	bInitialised = true;
}

void UCallbackDispatcher::Reset()
{
	ComponentUpdateCallbacks.Reset();
	AuthorityChangeCallbacks.Reset();
	QueuedUpdates.Reset();
	Callbacks.Reset();
	bInitialised = false;
}

void UCallbackDispatcher::AddComponentUpdateCallback(worker::EntityId EntityId, worker::ComponentId ComponentId, TFunction<void(UComponentUpdateOpWrapperBase&)> Callback)
{
	FComponentIdentifier Id{ EntityId, ComponentId };
	ComponentUpdateCallbacks.Emplace(Id, Callback);
	DispatchQueuedUpdates(Id);
}

void UCallbackDispatcher::AddAuthorityChangeCallback(worker::EntityId EntityId, worker::ComponentId ComponentId, TFunction<void(const worker::AuthorityChangeOp&)> Callback)
{
	AuthorityChangeCallbacks.Emplace(FComponentIdentifier{EntityId, ComponentId}, Callback);
}

void UCallbackDispatcher::RemoveComponentUpdateCallback(worker::EntityId EntityId, worker::ComponentId ComponentId)
{
	ComponentUpdateCallbacks.Remove(FComponentIdentifier{EntityId, ComponentId});
}

void UCallbackDispatcher::RemoveAuthorityChangeCallback(worker::EntityId EntityId, worker::ComponentId ComponentId)
{
	AuthorityChangeCallbacks.Remove(FComponentIdentifier{EntityId, ComponentId});
}

void UCallbackDispatcher::HandleUpdate(UComponentUpdateOpWrapperBase* Update)
{
	FComponentIdentifier Id{ Update->EntityId, Update->ComponentId };

	auto Callback = ComponentUpdateCallbacks.Find(Id);
	if (Callback != nullptr && (*Callback) != nullptr)
	{
		(*Callback)(*Update);
	}
	else
	{
		EnqueueUpdate(Id, Update);
	}
}

void UCallbackDispatcher::EnqueueUpdate(const FComponentIdentifier& Id, UComponentUpdateOpWrapperBase* Update)
{
	FComponentUpdateQueue* Queue = QueuedUpdates.Find(Id);
	if (!Queue)
	{
		Queue = &QueuedUpdates.Emplace(Id, FComponentUpdateQueue());
	}
	Queue->AddToQueue(Update);
}

void UCallbackDispatcher::DispatchQueuedUpdates(const FComponentIdentifier& Id)
{
	FComponentUpdateQueue* PendingUpdateQueue = QueuedUpdates.Find(Id);
	if (PendingUpdateQueue)
	{
		auto Callback = ComponentUpdateCallbacks.Find(Id);
		if (Callback != nullptr && (*Callback) != nullptr)
		{
			for (auto QueuedUpdate : PendingUpdateQueue->GetQueue())
			{
				(*Callback)(*QueuedUpdate);
			}
		}
		QueuedUpdates.Remove(Id);
	}
}

void UCallbackDispatcher::OnSpawnerComponentUpdateOp(const worker::ComponentUpdateOp<improbable::spawner::Spawner>& Op) {
	USpawnerComponentUpdate* WrappedUpdate = NewObject<USpawnerComponentUpdate>();
	if (WrappedUpdate)
	{
		WrappedUpdate->InitInternal(Op.Update);
		WrappedUpdate->ComponentId = improbable::spawner::Spawner::ComponentId;
		WrappedUpdate->EntityId = Op.EntityId;

		HandleUpdate(WrappedUpdate);
	}
}

void UCallbackDispatcher::OnSpawnerAuthorityChangeOp(const worker::AuthorityChangeOp& Op) {
	const worker::ComponentId ComponentId = improbable::spawner::Spawner::ComponentId;

	auto Callback = AuthorityChangeCallbacks.Find(FComponentIdentifier{Op.EntityId, ComponentId});
	if(Callback != nullptr && (*Callback) != nullptr)
	{
		(*Callback)(Op);
	}

	OnAuthorityChangeOpReceived.Broadcast(ComponentId, Op);
}

void UCallbackDispatcher::OnHeartbeatReceiverComponentUpdateOp(const worker::ComponentUpdateOp<improbable::player::HeartbeatReceiver>& Op) {
	UHeartbeatReceiverComponentUpdate* WrappedUpdate = NewObject<UHeartbeatReceiverComponentUpdate>();
	if (WrappedUpdate)
	{
		WrappedUpdate->InitInternal(Op.Update);
		WrappedUpdate->ComponentId = improbable::player::HeartbeatReceiver::ComponentId;
		WrappedUpdate->EntityId = Op.EntityId;

		HandleUpdate(WrappedUpdate);
	}
}

void UCallbackDispatcher::OnHeartbeatReceiverAuthorityChangeOp(const worker::AuthorityChangeOp& Op) {
	const worker::ComponentId ComponentId = improbable::player::HeartbeatReceiver::ComponentId;

	auto Callback = AuthorityChangeCallbacks.Find(FComponentIdentifier{Op.EntityId, ComponentId});
	if(Callback != nullptr && (*Callback) != nullptr)
	{
		(*Callback)(Op);
	}

	OnAuthorityChangeOpReceived.Broadcast(ComponentId, Op);
}

void UCallbackDispatcher::OnHeartbeatSenderComponentUpdateOp(const worker::ComponentUpdateOp<improbable::player::HeartbeatSender>& Op) {
	UHeartbeatSenderComponentUpdate* WrappedUpdate = NewObject<UHeartbeatSenderComponentUpdate>();
	if (WrappedUpdate)
	{
		WrappedUpdate->InitInternal(Op.Update);
		WrappedUpdate->ComponentId = improbable::player::HeartbeatSender::ComponentId;
		WrappedUpdate->EntityId = Op.EntityId;

		HandleUpdate(WrappedUpdate);
	}
}

void UCallbackDispatcher::OnHeartbeatSenderAuthorityChangeOp(const worker::AuthorityChangeOp& Op) {
	const worker::ComponentId ComponentId = improbable::player::HeartbeatSender::ComponentId;

	auto Callback = AuthorityChangeCallbacks.Find(FComponentIdentifier{Op.EntityId, ComponentId});
	if(Callback != nullptr && (*Callback) != nullptr)
	{
		(*Callback)(Op);
	}

	OnAuthorityChangeOpReceived.Broadcast(ComponentId, Op);
}

void UCallbackDispatcher::OnEntityAclComponentUpdateOp(const worker::ComponentUpdateOp<improbable::EntityAcl>& Op) {
	UEntityAclComponentUpdate* WrappedUpdate = NewObject<UEntityAclComponentUpdate>();
	if (WrappedUpdate)
	{
		WrappedUpdate->InitInternal(Op.Update);
		WrappedUpdate->ComponentId = improbable::EntityAcl::ComponentId;
		WrappedUpdate->EntityId = Op.EntityId;

		HandleUpdate(WrappedUpdate);
	}
}

void UCallbackDispatcher::OnEntityAclAuthorityChangeOp(const worker::AuthorityChangeOp& Op) {
	const worker::ComponentId ComponentId = improbable::EntityAcl::ComponentId;

	auto Callback = AuthorityChangeCallbacks.Find(FComponentIdentifier{Op.EntityId, ComponentId});
	if(Callback != nullptr && (*Callback) != nullptr)
	{
		(*Callback)(Op);
	}

	OnAuthorityChangeOpReceived.Broadcast(ComponentId, Op);
}

void UCallbackDispatcher::OnMetadataComponentUpdateOp(const worker::ComponentUpdateOp<improbable::Metadata>& Op) {
	UMetadataComponentUpdate* WrappedUpdate = NewObject<UMetadataComponentUpdate>();
	if (WrappedUpdate)
	{
		WrappedUpdate->InitInternal(Op.Update);
		WrappedUpdate->ComponentId = improbable::Metadata::ComponentId;
		WrappedUpdate->EntityId = Op.EntityId;

		HandleUpdate(WrappedUpdate);
	}
}

void UCallbackDispatcher::OnMetadataAuthorityChangeOp(const worker::AuthorityChangeOp& Op) {
	const worker::ComponentId ComponentId = improbable::Metadata::ComponentId;

	auto Callback = AuthorityChangeCallbacks.Find(FComponentIdentifier{Op.EntityId, ComponentId});
	if(Callback != nullptr && (*Callback) != nullptr)
	{
		(*Callback)(Op);
	}

	OnAuthorityChangeOpReceived.Broadcast(ComponentId, Op);
}

void UCallbackDispatcher::OnPositionComponentUpdateOp(const worker::ComponentUpdateOp<improbable::Position>& Op) {
	UPositionComponentUpdate* WrappedUpdate = NewObject<UPositionComponentUpdate>();
	if (WrappedUpdate)
	{
		WrappedUpdate->InitInternal(Op.Update);
		WrappedUpdate->ComponentId = improbable::Position::ComponentId;
		WrappedUpdate->EntityId = Op.EntityId;

		HandleUpdate(WrappedUpdate);
	}
}

void UCallbackDispatcher::OnPositionAuthorityChangeOp(const worker::AuthorityChangeOp& Op) {
	const worker::ComponentId ComponentId = improbable::Position::ComponentId;

	auto Callback = AuthorityChangeCallbacks.Find(FComponentIdentifier{Op.EntityId, ComponentId});
	if(Callback != nullptr && (*Callback) != nullptr)
	{
		(*Callback)(Op);
	}

	OnAuthorityChangeOpReceived.Broadcast(ComponentId, Op);
}

void UCallbackDispatcher::OnPersistenceComponentUpdateOp(const worker::ComponentUpdateOp<improbable::Persistence>& Op) {
	UPersistenceComponentUpdate* WrappedUpdate = NewObject<UPersistenceComponentUpdate>();
	if (WrappedUpdate)
	{
		WrappedUpdate->InitInternal(Op.Update);
		WrappedUpdate->ComponentId = improbable::Persistence::ComponentId;
		WrappedUpdate->EntityId = Op.EntityId;

		HandleUpdate(WrappedUpdate);
	}
}

void UCallbackDispatcher::OnPersistenceAuthorityChangeOp(const worker::AuthorityChangeOp& Op) {
	const worker::ComponentId ComponentId = improbable::Persistence::ComponentId;

	auto Callback = AuthorityChangeCallbacks.Find(FComponentIdentifier{Op.EntityId, ComponentId});
	if(Callback != nullptr && (*Callback) != nullptr)
	{
		(*Callback)(Op);
	}

	OnAuthorityChangeOpReceived.Broadcast(ComponentId, Op);
}

