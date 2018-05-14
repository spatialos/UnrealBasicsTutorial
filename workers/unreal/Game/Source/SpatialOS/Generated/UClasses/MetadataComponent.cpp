// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "MetadataComponent.h"
#include "CallbackDispatcher.h"

#include "SpatialOSViewTypes.h"

const worker::ComponentId UMetadataComponent::ComponentId = 53;

UMetadataComponent::UMetadataComponent()
: ComponentUpdater(nullptr)
, Snapshot(nullptr)
{
}

void UMetadataComponent::BeginDestroy()
{
	Super::BeginDestroy();

	Callbacks.Reset(nullptr);
	
	delete Snapshot;
	Snapshot = nullptr;
}

FComponentId UMetadataComponent::GetComponentId()
{
    return FComponentId(ComponentId);
}

void UMetadataComponent::Init(const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView,
                          worker::EntityId InEntityId, UCallbackDispatcher* InCallbackDispatcher)
{
    USpatialOsComponent::Init(InConnection, InView, InEntityId, InCallbackDispatcher);

	InCallbackDispatcher->AddComponentUpdateCallback(InEntityId, ComponentId, [this](UComponentUpdateOpWrapperBase& Op) { OnComponentUpdateDispatcherCallback(Op); });
	InCallbackDispatcher->AddAuthorityChangeCallback(InEntityId, ComponentId, [this](const worker::AuthorityChangeOp& Op) { OnAuthorityChangeDispatcherCallback(Op); });
	ComponentUpdater = NewObject<UMetadataComponentUpdate>(this);

	auto LockedView = View.Pin();
	if(LockedView.IsValid())
	{
	
	}
}

void  UMetadataComponent::Disable(const worker::EntityId InEntityId, UCallbackDispatcher* CallbackDispatcher)
{
	if(CallbackDispatcher)
	{
		CallbackDispatcher->RemoveComponentUpdateCallback(InEntityId, ComponentId);
		CallbackDispatcher->RemoveAuthorityChangeCallback(InEntityId, ComponentId);
	}
}

void UMetadataComponent::SendComponentUpdate(UMetadataComponentUpdate* update)
{
	SendComponentUpdateInternal(update);
}

void UMetadataComponent::ApplyInitialState(const UAddComponentOpWrapperBase& AddComponentOp)
{
	const UMetadataAddComponentOp& DerivedOp = dynamic_cast<const UMetadataAddComponentOp&>(AddComponentOp);
    auto update = improbable::Metadata::Update::FromInitialData(*(DerivedOp.Data.data()));
    ApplyComponentUpdate(update);
}

void UMetadataComponent::GenerateSnapshot()
{
	if (Snapshot)
	{
		return;
	}

	Snapshot = new FMetadataComponentSnapshot();
	check(Snapshot);

	Snapshot->EntityType = EntityType;
}

void UMetadataComponent::ReplicateChanges(float DeltaSeconds)
{
	TriggerAutomaticComponentUpdate(DeltaSeconds);
}

void UMetadataComponent::TriggerAutomaticComponentUpdate(float DeltaSeconds)
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

void UMetadataComponent::TriggerManualComponentUpdate()
{
	if (GetAuthority() == EAuthority::NotAuthoritative)
	{
		return;
	}

	ReplicateChangesInternal();
}



void UMetadataComponent::OnComponentUpdateDispatcherCallback(UComponentUpdateOpWrapperBase& Op)
{
	UMetadataComponentUpdate& ThisOp = dynamic_cast<UMetadataComponentUpdate&>(Op);
    ApplyComponentUpdate(ThisOp.GetUnderlyingInternal());
}

void UMetadataComponent::OnAuthorityChangeDispatcherCallback(const worker::AuthorityChangeOp& Op)
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

void UMetadataComponent::ReplicateChangesInternal()
{
	checkSlow(Snapshot);
		
	bool bShouldSendUpdate = false;
		
	if (EntityType != Snapshot->EntityType)
	{
		ComponentUpdater->SetEntityTypeInternal(EntityType);
		Snapshot->EntityType = EntityType;
		bShouldSendUpdate = true;
	}
	bShouldSendUpdate |= bHasEventQueued;
	if (bShouldSendUpdate)
	{
		SendComponentUpdateInternal(ComponentUpdater);
		ComponentUpdater->ResetInternal();
		bHasEventQueued = false;
	}
}

void UMetadataComponent::SendComponentUpdateInternal(UMetadataComponentUpdate* update)
{
	auto LockedConnection = Connection.Pin();

	if(LockedConnection.IsValid())
	{
	    LockedConnection->SendComponentUpdate<improbable::Metadata>(EntityId, update->GetUnderlyingInternal());
	}
}

void UMetadataComponent::ApplyComponentUpdate(const improbable::Metadata::Update& update)
{
    if (!update.entity_type().empty())
    {
		EntityType = FString((*(update.entity_type().data())).c_str());
    }


	NotifyUpdate(update);
}

void UMetadataComponent::NotifyUpdate(const improbable::Metadata::Update& update)
{
    if (!update.entity_type().empty())
    {
        OnEntityTypeUpdate.Broadcast();
    }


    OnComponentUpdate.Broadcast();

    if (!bIsComponentReady)
    {
        bIsComponentReady = true;
        OnComponentReady.Broadcast();
    }
}

FString UMetadataComponent::GetEntityType()
{
    return EntityType;
}

