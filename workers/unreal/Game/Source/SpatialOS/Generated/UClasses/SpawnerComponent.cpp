// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "SpawnerComponent.h"
#include "CallbackDispatcher.h"

#include "SpawnPlayerRequest.h"
#include "SpatialOSViewTypes.h"

const worker::ComponentId USpawnerComponent::ComponentId = 21010;

USpawnerComponent::USpawnerComponent()
: ComponentUpdater(nullptr)
, Snapshot(nullptr)
{
}

void USpawnerComponent::BeginDestroy()
{
	Super::BeginDestroy();

	Callbacks.Reset(nullptr);
	
	delete Snapshot;
	Snapshot = nullptr;
}

FComponentId USpawnerComponent::GetComponentId()
{
    return FComponentId(ComponentId);
}

void USpawnerComponent::Init(const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView,
                          worker::EntityId InEntityId, UCallbackDispatcher* InCallbackDispatcher)
{
    USpatialOsComponent::Init(InConnection, InView, InEntityId, InCallbackDispatcher);

	InCallbackDispatcher->AddComponentUpdateCallback(InEntityId, ComponentId, [this](UComponentUpdateOpWrapperBase& Op) { OnComponentUpdateDispatcherCallback(Op); });
	InCallbackDispatcher->AddAuthorityChangeCallback(InEntityId, ComponentId, [this](const worker::AuthorityChangeOp& Op) { OnAuthorityChangeDispatcherCallback(Op); });
	ComponentUpdater = NewObject<USpawnerComponentUpdate>(this);

	auto LockedView = View.Pin();
	if(LockedView.IsValid())
	{
		Callbacks->Add(LockedView->OnCommandRequest<improbable::spawner::Spawner::Commands::SpawnPlayer>(
			std::bind(&USpawnerComponent::OnSpawnPlayerCommandRequestDispatcherCallback, this,
					  std::placeholders::_1)));
	
	}
}

void  USpawnerComponent::Disable(const worker::EntityId InEntityId, UCallbackDispatcher* CallbackDispatcher)
{
	if(CallbackDispatcher)
	{
		CallbackDispatcher->RemoveComponentUpdateCallback(InEntityId, ComponentId);
		CallbackDispatcher->RemoveAuthorityChangeCallback(InEntityId, ComponentId);
	}
}

void USpawnerComponent::SendComponentUpdate(USpawnerComponentUpdate* update)
{
	SendComponentUpdateInternal(update);
}

void USpawnerComponent::ApplyInitialState(const UAddComponentOpWrapperBase& AddComponentOp)
{
	const USpawnerAddComponentOp& DerivedOp = dynamic_cast<const USpawnerAddComponentOp&>(AddComponentOp);
    auto update = improbable::spawner::Spawner::Update::FromInitialData(*(DerivedOp.Data.data()));
    ApplyComponentUpdate(update);
}

void USpawnerComponent::GenerateSnapshot()
{
	if (Snapshot)
	{
		return;
	}

	Snapshot = new FSpawnerComponentSnapshot();
	check(Snapshot);

}

void USpawnerComponent::ReplicateChanges(float DeltaSeconds)
{
	TriggerAutomaticComponentUpdate(DeltaSeconds);
}

void USpawnerComponent::TriggerAutomaticComponentUpdate(float DeltaSeconds)
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

void USpawnerComponent::TriggerManualComponentUpdate()
{
	if (GetAuthority() == EAuthority::NotAuthoritative)
	{
		return;
	}

	ReplicateChangesInternal();
}



void USpawnerComponent::OnComponentUpdateDispatcherCallback(UComponentUpdateOpWrapperBase& Op)
{
	USpawnerComponentUpdate& ThisOp = dynamic_cast<USpawnerComponentUpdate&>(Op);
    ApplyComponentUpdate(ThisOp.GetUnderlyingInternal());
}

void USpawnerComponent::OnAuthorityChangeDispatcherCallback(const worker::AuthorityChangeOp& Op)
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

void USpawnerComponent::ReplicateChangesInternal()
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

void USpawnerComponent::SendComponentUpdateInternal(USpawnerComponentUpdate* update)
{
	auto LockedConnection = Connection.Pin();

	if(LockedConnection.IsValid())
	{
	    LockedConnection->SendComponentUpdate<improbable::spawner::Spawner>(EntityId, update->GetUnderlyingInternal());
	}
}

void USpawnerComponent::ApplyComponentUpdate(const improbable::spawner::Spawner::Update& update)
{

	NotifyUpdate(update);
}

void USpawnerComponent::NotifyUpdate(const improbable::spawner::Spawner::Update& update)
{

    OnComponentUpdate.Broadcast();

    if (!bIsComponentReady)
    {
        bIsComponentReady = true;
        OnComponentReady.Broadcast();
    }
}


void USpawnerComponent::OnSpawnPlayerCommandRequestDispatcherCallback(
    const worker::CommandRequestOp<improbable::spawner::Spawner::Commands::SpawnPlayer>& op)
{
    if (op.EntityId != EntityId)
    {
        return;
    }
    auto request = NewObject<USpawnPlayerRequest>()->Init(op.Request);
	
	USpawnPlayerCommandResponder* SpawnPlayerResponder = NewObject<USpawnPlayerCommandResponder>(this);
	SpawnPlayerResponder->Init(Connection, op.RequestId, request, op.CallerWorkerId);
	
    OnSpawnPlayerCommandRequest.Broadcast(SpawnPlayerResponder);
}
