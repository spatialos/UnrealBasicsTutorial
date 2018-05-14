// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "PositionComponent.h"
#include "CallbackDispatcher.h"

#include "SpatialOSViewTypes.h"

const worker::ComponentId UPositionComponent::ComponentId = 54;

UPositionComponent::UPositionComponent()
: ComponentUpdater(nullptr)
, Snapshot(nullptr)
{
}

void UPositionComponent::BeginDestroy()
{
	Super::BeginDestroy();

	Callbacks.Reset(nullptr);
	
	delete Snapshot;
	Snapshot = nullptr;
}

FComponentId UPositionComponent::GetComponentId()
{
    return FComponentId(ComponentId);
}

void UPositionComponent::Init(const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView,
                          worker::EntityId InEntityId, UCallbackDispatcher* InCallbackDispatcher)
{
    USpatialOsComponent::Init(InConnection, InView, InEntityId, InCallbackDispatcher);

	InCallbackDispatcher->AddComponentUpdateCallback(InEntityId, ComponentId, [this](UComponentUpdateOpWrapperBase& Op) { OnComponentUpdateDispatcherCallback(Op); });
	InCallbackDispatcher->AddAuthorityChangeCallback(InEntityId, ComponentId, [this](const worker::AuthorityChangeOp& Op) { OnAuthorityChangeDispatcherCallback(Op); });
	ComponentUpdater = NewObject<UPositionComponentUpdate>(this);

	auto LockedView = View.Pin();
	if(LockedView.IsValid())
	{
	
	}
}

void  UPositionComponent::Disable(const worker::EntityId InEntityId, UCallbackDispatcher* CallbackDispatcher)
{
	if(CallbackDispatcher)
	{
		CallbackDispatcher->RemoveComponentUpdateCallback(InEntityId, ComponentId);
		CallbackDispatcher->RemoveAuthorityChangeCallback(InEntityId, ComponentId);
	}
}

void UPositionComponent::SendComponentUpdate(UPositionComponentUpdate* update)
{
	SendComponentUpdateInternal(update);
}

void UPositionComponent::ApplyInitialState(const UAddComponentOpWrapperBase& AddComponentOp)
{
	const UPositionAddComponentOp& DerivedOp = dynamic_cast<const UPositionAddComponentOp&>(AddComponentOp);
    auto update = improbable::Position::Update::FromInitialData(*(DerivedOp.Data.data()));
    ApplyComponentUpdate(update);
}

void UPositionComponent::GenerateSnapshot()
{
	if (Snapshot)
	{
		return;
	}

	Snapshot = new FPositionComponentSnapshot();
	check(Snapshot);

	Snapshot->Coords = Coords;
}

void UPositionComponent::ReplicateChanges(float DeltaSeconds)
{
	TriggerAutomaticComponentUpdate(DeltaSeconds);
}

void UPositionComponent::TriggerAutomaticComponentUpdate(float DeltaSeconds)
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

void UPositionComponent::TriggerManualComponentUpdate()
{
	if (GetAuthority() == EAuthority::NotAuthoritative)
	{
		return;
	}

	ReplicateChangesInternal();
}



void UPositionComponent::OnComponentUpdateDispatcherCallback(UComponentUpdateOpWrapperBase& Op)
{
	UPositionComponentUpdate& ThisOp = dynamic_cast<UPositionComponentUpdate&>(Op);
    ApplyComponentUpdate(ThisOp.GetUnderlyingInternal());
}

void UPositionComponent::OnAuthorityChangeDispatcherCallback(const worker::AuthorityChangeOp& Op)
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

void UPositionComponent::ReplicateChangesInternal()
{
	checkSlow(Snapshot);
		
	bool bShouldSendUpdate = false;
		
	if (!Coords.Equals(Snapshot->Coords))
	{
		ComponentUpdater->SetCoordsInternal(Coords);
		Snapshot->Coords = Coords;
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

void UPositionComponent::SendComponentUpdateInternal(UPositionComponentUpdate* update)
{
	auto LockedConnection = Connection.Pin();

	if(LockedConnection.IsValid())
	{
	    LockedConnection->SendComponentUpdate<improbable::Position>(EntityId, update->GetUnderlyingInternal());
	}
}

void UPositionComponent::ApplyComponentUpdate(const improbable::Position::Update& update)
{
    if (!update.coords().empty())
    {
		Coords = USpatialOSConversionFunctionLibrary::SpatialOsCoordinatesToUnrealCoordinates(FVector(static_cast<float>((*(update.coords().data())).x()), static_cast<float>((*(update.coords().data())).y()), static_cast<float>((*(update.coords().data())).z())));
    }


	NotifyUpdate(update);
}

void UPositionComponent::NotifyUpdate(const improbable::Position::Update& update)
{
    if (!update.coords().empty())
    {
        OnCoordsUpdate.Broadcast();
    }


    OnComponentUpdate.Broadcast();

    if (!bIsComponentReady)
    {
        bIsComponentReady = true;
        OnComponentReady.Broadcast();
    }
}

FVector UPositionComponent::GetCoords()
{
    return Coords;
}

