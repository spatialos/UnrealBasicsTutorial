// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "HeartbeatReceiverComponent.h"
#include "CallbackDispatcher.h"

#include "HeartbeatRequest.h"
#include "SpatialOSViewTypes.h"

const worker::ComponentId UHeartbeatReceiverComponent::ComponentId = 21001;

UHeartbeatReceiverComponent::UHeartbeatReceiverComponent()
: ComponentUpdater(nullptr)
, Snapshot(nullptr)
{
}

void UHeartbeatReceiverComponent::BeginDestroy()
{
	Super::BeginDestroy();

	Callbacks.Reset(nullptr);
	
	delete Snapshot;
	Snapshot = nullptr;
}

FComponentId UHeartbeatReceiverComponent::GetComponentId()
{
    return FComponentId(ComponentId);
}

void UHeartbeatReceiverComponent::Init(const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView,
                          worker::EntityId InEntityId, UCallbackDispatcher* InCallbackDispatcher)
{
    USpatialOsComponent::Init(InConnection, InView, InEntityId, InCallbackDispatcher);

	InCallbackDispatcher->AddComponentUpdateCallback(InEntityId, ComponentId, [this](UComponentUpdateOpWrapperBase& Op) { OnComponentUpdateDispatcherCallback(Op); });
	InCallbackDispatcher->AddAuthorityChangeCallback(InEntityId, ComponentId, [this](const worker::AuthorityChangeOp& Op) { OnAuthorityChangeDispatcherCallback(Op); });
	ComponentUpdater = NewObject<UHeartbeatReceiverComponentUpdate>(this);

	auto LockedView = View.Pin();
	if(LockedView.IsValid())
	{
		Callbacks->Add(LockedView->OnCommandRequest<improbable::player::HeartbeatReceiver::Commands::Heartbeat>(
			std::bind(&UHeartbeatReceiverComponent::OnHeartbeatCommandRequestDispatcherCallback, this,
					  std::placeholders::_1)));
	
	}
}

void  UHeartbeatReceiverComponent::Disable(const worker::EntityId InEntityId, UCallbackDispatcher* CallbackDispatcher)
{
	if(CallbackDispatcher)
	{
		CallbackDispatcher->RemoveComponentUpdateCallback(InEntityId, ComponentId);
		CallbackDispatcher->RemoveAuthorityChangeCallback(InEntityId, ComponentId);
	}
}

void UHeartbeatReceiverComponent::SendComponentUpdate(UHeartbeatReceiverComponentUpdate* update)
{
	SendComponentUpdateInternal(update);
}

void UHeartbeatReceiverComponent::ApplyInitialState(const UAddComponentOpWrapperBase& AddComponentOp)
{
	const UHeartbeatReceiverAddComponentOp& DerivedOp = dynamic_cast<const UHeartbeatReceiverAddComponentOp&>(AddComponentOp);
    auto update = improbable::player::HeartbeatReceiver::Update::FromInitialData(*(DerivedOp.Data.data()));
    ApplyComponentUpdate(update);
}

void UHeartbeatReceiverComponent::GenerateSnapshot()
{
	if (Snapshot)
	{
		return;
	}

	Snapshot = new FHeartbeatReceiverComponentSnapshot();
	check(Snapshot);

}

void UHeartbeatReceiverComponent::ReplicateChanges(float DeltaSeconds)
{
	TriggerAutomaticComponentUpdate(DeltaSeconds);
}

void UHeartbeatReceiverComponent::TriggerAutomaticComponentUpdate(float DeltaSeconds)
{
	if (GetAuthority() == EAuthority::NotAuthoritative || MaxUpdatesPerSecond == 0)
	{
		return;
	}

	TimeUntilNextUpdate -= DeltaSeconds;
	if (TimeUntilNextUpdate > 0.0f)
	{
		return;
	}

	TimeUntilNextUpdate = 1.0f / static_cast<float>(MaxUpdatesPerSecond);

	ReplicateChangesInternal();
}

void UHeartbeatReceiverComponent::TriggerManualComponentUpdate()
{
	if (GetAuthority() == EAuthority::NotAuthoritative)
	{
		return;
	}

	ReplicateChangesInternal();
}



void UHeartbeatReceiverComponent::OnComponentUpdateDispatcherCallback(UComponentUpdateOpWrapperBase& Op)
{
	UHeartbeatReceiverComponentUpdate& ThisOp = dynamic_cast<UHeartbeatReceiverComponentUpdate&>(Op);
    ApplyComponentUpdate(ThisOp.GetUnderlyingInternal());
}

void UHeartbeatReceiverComponent::OnAuthorityChangeDispatcherCallback(const worker::AuthorityChangeOp& Op)
{
	if (Op.Authority == worker::Authority::kNotAuthoritative)
	{
		delete Snapshot;
		Snapshot = nullptr;
	}
	else
	{
		GenerateSnapshot();
	}

	Super::OnAuthorityChangeDispatcherCallback(Op);	
}

void UHeartbeatReceiverComponent::ReplicateChangesInternal()
{
	checkSlow(Snapshot);
		
	bool bShouldSendUpdate = false;
		
	bShouldSendUpdate |= bHasEventQueued;
	if (bShouldSendUpdate)
	{
		SendComponentUpdateInternal(ComponentUpdater);
		ComponentUpdater->ResetInternal();
		bHasEventQueued = false;
	}
}

void UHeartbeatReceiverComponent::SendComponentUpdateInternal(UHeartbeatReceiverComponentUpdate* update)
{
	auto LockedConnection = Connection.Pin();

	if(LockedConnection.IsValid())
	{
	    LockedConnection->SendComponentUpdate<improbable::player::HeartbeatReceiver>(EntityId, update->GetUnderlyingInternal());
	}
}

void UHeartbeatReceiverComponent::ApplyComponentUpdate(const improbable::player::HeartbeatReceiver::Update& update)
{

	NotifyUpdate(update);
}

void UHeartbeatReceiverComponent::NotifyUpdate(const improbable::player::HeartbeatReceiver::Update& update)
{

    OnComponentUpdate.Broadcast();

    if (!bIsComponentReady)
    {
        bIsComponentReady = true;
        OnComponentReady.Broadcast();
    }
}


void UHeartbeatReceiverComponent::OnHeartbeatCommandRequestDispatcherCallback(
    const worker::CommandRequestOp<improbable::player::HeartbeatReceiver::Commands::Heartbeat>& op)
{
    if (op.EntityId != EntityId)
    {
        return;
    }
    auto request = NewObject<UHeartbeatRequest>()->Init(op.Request);
	
	UHeartbeatCommandResponder* HeartbeatResponder = NewObject<UHeartbeatCommandResponder>(this);
	HeartbeatResponder->Init(Connection, op.RequestId, request, op.CallerWorkerId);
	
    OnHeartbeatCommandRequest.Broadcast(HeartbeatResponder);
}
