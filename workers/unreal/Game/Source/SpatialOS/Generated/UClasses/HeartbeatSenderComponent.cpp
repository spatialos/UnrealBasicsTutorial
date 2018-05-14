// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "HeartbeatSenderComponent.h"
#include "CallbackDispatcher.h"

#include "SpatialOSViewTypes.h"

const worker::ComponentId UHeartbeatSenderComponent::ComponentId = 21002;

UHeartbeatSenderComponent::UHeartbeatSenderComponent()
: ComponentUpdater(nullptr)
, Snapshot(nullptr)
{
}

void UHeartbeatSenderComponent::BeginDestroy()
{
	Super::BeginDestroy();

	Callbacks.Reset(nullptr);
	
	delete Snapshot;
	Snapshot = nullptr;
}

FComponentId UHeartbeatSenderComponent::GetComponentId()
{
    return FComponentId(ComponentId);
}

void UHeartbeatSenderComponent::Init(const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView,
                          worker::EntityId InEntityId, UCallbackDispatcher* InCallbackDispatcher)
{
    USpatialOsComponent::Init(InConnection, InView, InEntityId, InCallbackDispatcher);

	InCallbackDispatcher->AddComponentUpdateCallback(InEntityId, ComponentId, [this](UComponentUpdateOpWrapperBase& Op) { OnComponentUpdateDispatcherCallback(Op); });
	InCallbackDispatcher->AddAuthorityChangeCallback(InEntityId, ComponentId, [this](const worker::AuthorityChangeOp& Op) { OnAuthorityChangeDispatcherCallback(Op); });
	ComponentUpdater = NewObject<UHeartbeatSenderComponentUpdate>(this);

	auto LockedView = View.Pin();
	if(LockedView.IsValid())
	{
	
	}
}

void  UHeartbeatSenderComponent::Disable(const worker::EntityId InEntityId, UCallbackDispatcher* CallbackDispatcher)
{
	if(CallbackDispatcher)
	{
		CallbackDispatcher->RemoveComponentUpdateCallback(InEntityId, ComponentId);
		CallbackDispatcher->RemoveAuthorityChangeCallback(InEntityId, ComponentId);
	}
}

void UHeartbeatSenderComponent::SendComponentUpdate(UHeartbeatSenderComponentUpdate* update)
{
	SendComponentUpdateInternal(update);
}

void UHeartbeatSenderComponent::ApplyInitialState(const UAddComponentOpWrapperBase& AddComponentOp)
{
	const UHeartbeatSenderAddComponentOp& DerivedOp = dynamic_cast<const UHeartbeatSenderAddComponentOp&>(AddComponentOp);
    auto update = improbable::player::HeartbeatSender::Update::FromInitialData(*(DerivedOp.Data.data()));
    ApplyComponentUpdate(update);
}

void UHeartbeatSenderComponent::GenerateSnapshot()
{
	if (Snapshot)
	{
		return;
	}

	Snapshot = new FHeartbeatSenderComponentSnapshot();
	check(Snapshot);

}

void UHeartbeatSenderComponent::ReplicateChanges(float DeltaSeconds)
{
	TriggerAutomaticComponentUpdate(DeltaSeconds);
}

void UHeartbeatSenderComponent::TriggerAutomaticComponentUpdate(float DeltaSeconds)
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

void UHeartbeatSenderComponent::TriggerManualComponentUpdate()
{
	if (GetAuthority() == EAuthority::NotAuthoritative)
	{
		return;
	}

	ReplicateChangesInternal();
}



void UHeartbeatSenderComponent::OnComponentUpdateDispatcherCallback(UComponentUpdateOpWrapperBase& Op)
{
	UHeartbeatSenderComponentUpdate& ThisOp = dynamic_cast<UHeartbeatSenderComponentUpdate&>(Op);
    ApplyComponentUpdate(ThisOp.GetUnderlyingInternal());
}

void UHeartbeatSenderComponent::OnAuthorityChangeDispatcherCallback(const worker::AuthorityChangeOp& Op)
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

void UHeartbeatSenderComponent::ReplicateChangesInternal()
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

void UHeartbeatSenderComponent::SendComponentUpdateInternal(UHeartbeatSenderComponentUpdate* update)
{
	auto LockedConnection = Connection.Pin();

	if(LockedConnection.IsValid())
	{
	    LockedConnection->SendComponentUpdate<improbable::player::HeartbeatSender>(EntityId, update->GetUnderlyingInternal());
	}
}

void UHeartbeatSenderComponent::ApplyComponentUpdate(const improbable::player::HeartbeatSender::Update& update)
{

	NotifyUpdate(update);
}

void UHeartbeatSenderComponent::NotifyUpdate(const improbable::player::HeartbeatSender::Update& update)
{

    OnComponentUpdate.Broadcast();

    if (!bIsComponentReady)
    {
        bIsComponentReady = true;
        OnComponentReady.Broadcast();
    }
}


