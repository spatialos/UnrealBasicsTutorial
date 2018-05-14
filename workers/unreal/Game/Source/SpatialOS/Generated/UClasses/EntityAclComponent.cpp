// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "EntityAclComponent.h"
#include "CallbackDispatcher.h"

#include "SpatialOSViewTypes.h"

const worker::ComponentId UEntityAclComponent::ComponentId = 50;

UEntityAclComponent::UEntityAclComponent()
: ReadAcl(nullptr)
, ComponentWriteAcl(nullptr)
, ComponentUpdater(nullptr)
, Snapshot(nullptr)
{
}

void UEntityAclComponent::BeginDestroy()
{
	Super::BeginDestroy();

	Callbacks.Reset(nullptr);
	
	delete Snapshot;
	Snapshot = nullptr;
}

FComponentId UEntityAclComponent::GetComponentId()
{
    return FComponentId(ComponentId);
}

void UEntityAclComponent::Init(const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView,
                          worker::EntityId InEntityId, UCallbackDispatcher* InCallbackDispatcher)
{
    USpatialOsComponent::Init(InConnection, InView, InEntityId, InCallbackDispatcher);

	InCallbackDispatcher->AddComponentUpdateCallback(InEntityId, ComponentId, [this](UComponentUpdateOpWrapperBase& Op) { OnComponentUpdateDispatcherCallback(Op); });
	InCallbackDispatcher->AddAuthorityChangeCallback(InEntityId, ComponentId, [this](const worker::AuthorityChangeOp& Op) { OnAuthorityChangeDispatcherCallback(Op); });
	ComponentUpdater = NewObject<UEntityAclComponentUpdate>(this);

	auto LockedView = View.Pin();
	if(LockedView.IsValid())
	{
	
	}
}

void  UEntityAclComponent::Disable(const worker::EntityId InEntityId, UCallbackDispatcher* CallbackDispatcher)
{
	if(CallbackDispatcher)
	{
		CallbackDispatcher->RemoveComponentUpdateCallback(InEntityId, ComponentId);
		CallbackDispatcher->RemoveAuthorityChangeCallback(InEntityId, ComponentId);
	}
}

void UEntityAclComponent::SendComponentUpdate(UEntityAclComponentUpdate* update)
{
	SendComponentUpdateInternal(update);
}

void UEntityAclComponent::ApplyInitialState(const UAddComponentOpWrapperBase& AddComponentOp)
{
	const UEntityAclAddComponentOp& DerivedOp = dynamic_cast<const UEntityAclAddComponentOp&>(AddComponentOp);
    auto update = improbable::EntityAcl::Update::FromInitialData(*(DerivedOp.Data.data()));
    ApplyComponentUpdate(update);
}

void UEntityAclComponent::GenerateSnapshot()
{
	if (Snapshot)
	{
		return;
	}

	Snapshot = new FEntityAclComponentSnapshot();
	check(Snapshot);

	Snapshot->ReadAcl = ReadAcl->GetUnderlying();
	Snapshot->ComponentWriteAcl = ComponentWriteAcl->GetUnderlying();
}

void UEntityAclComponent::ReplicateChanges(float DeltaSeconds)
{
	TriggerAutomaticComponentUpdate(DeltaSeconds);
}

void UEntityAclComponent::TriggerAutomaticComponentUpdate(float DeltaSeconds)
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

void UEntityAclComponent::TriggerManualComponentUpdate()
{
	if (GetAuthority() == EAuthority::NotAuthoritative)
	{
		return;
	}

	ReplicateChangesInternal();
}



void UEntityAclComponent::OnComponentUpdateDispatcherCallback(UComponentUpdateOpWrapperBase& Op)
{
	UEntityAclComponentUpdate& ThisOp = dynamic_cast<UEntityAclComponentUpdate&>(Op);
    ApplyComponentUpdate(ThisOp.GetUnderlyingInternal());
}

void UEntityAclComponent::OnAuthorityChangeDispatcherCallback(const worker::AuthorityChangeOp& Op)
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

void UEntityAclComponent::ReplicateChangesInternal()
{
	checkSlow(Snapshot);
		
	bool bShouldSendUpdate = false;
		
	if (ReadAcl && (ReadAcl->GetUnderlying() != Snapshot->ReadAcl))
	{
		ComponentUpdater->SetReadAclInternal(ReadAcl);
		Snapshot->ReadAcl = ReadAcl->GetUnderlying();
		bShouldSendUpdate = true;
	}
	if (ComponentWriteAcl && (*ComponentWriteAcl != Snapshot->ComponentWriteAcl))
	{
		ComponentUpdater->SetComponentWriteAclInternal(ComponentWriteAcl);
		Snapshot->ComponentWriteAcl = ComponentWriteAcl->GetUnderlying();
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

void UEntityAclComponent::SendComponentUpdateInternal(UEntityAclComponentUpdate* update)
{
	auto LockedConnection = Connection.Pin();

	if(LockedConnection.IsValid())
	{
	    LockedConnection->SendComponentUpdate<improbable::EntityAcl>(EntityId, update->GetUnderlyingInternal());
	}
}

void UEntityAclComponent::ApplyComponentUpdate(const improbable::EntityAcl::Update& update)
{
    if (!update.read_acl().empty())
    {
		if (ReadAcl == nullptr) { ReadAcl = NewObject<UWorkerRequirementSet>(this); } ReadAcl->Init((*(update.read_acl().data())));
    }

    if (!update.component_write_acl().empty())
    {
		if (ComponentWriteAcl == nullptr) { ComponentWriteAcl = NewObject<UStdUint32TToImprobableWorkerRequirementSetMap>(this); } ComponentWriteAcl->Init((*(update.component_write_acl().data())));
    }


	NotifyUpdate(update);
}

void UEntityAclComponent::NotifyUpdate(const improbable::EntityAcl::Update& update)
{
    if (!update.read_acl().empty())
    {
        OnReadAclUpdate.Broadcast();
    }

    if (!update.component_write_acl().empty())
    {
        OnComponentWriteAclUpdate.Broadcast();
    }


    OnComponentUpdate.Broadcast();

    if (!bIsComponentReady)
    {
        bIsComponentReady = true;
        OnComponentReady.Broadcast();
    }
}

UWorkerRequirementSet* UEntityAclComponent::GetReadAcl()
{
    return ReadAcl;
}
UStdUint32TToImprobableWorkerRequirementSetMap* UEntityAclComponent::GetComponentWriteAcl()
{
    return ComponentWriteAcl;
}

