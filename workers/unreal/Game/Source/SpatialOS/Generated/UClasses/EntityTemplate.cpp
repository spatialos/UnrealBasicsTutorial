// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "EntityTemplate.h"

UEntityTemplate::UEntityTemplate()
{
}

UEntityTemplate* UEntityTemplate::Init(const worker::Entity& underlying)
{
    Underlying = worker::Entity(underlying);
    return this;
}

UEntityTemplate* UEntityTemplate::AddSpawnerComponent(USpawnerData* data)
{
    Underlying.Add<improbable::spawner::Spawner>(data->GetUnderlying());
	return this;
}

UEntityTemplate* UEntityTemplate::AddHeartbeatReceiverComponent(UHeartbeatReceiverData* data)
{
    Underlying.Add<improbable::player::HeartbeatReceiver>(data->GetUnderlying());
	return this;
}

UEntityTemplate* UEntityTemplate::AddHeartbeatSenderComponent(UHeartbeatSenderData* data)
{
    Underlying.Add<improbable::player::HeartbeatSender>(data->GetUnderlying());
	return this;
}

UEntityTemplate* UEntityTemplate::AddEntityAclComponent(UEntityAclData* data)
{
    Underlying.Add<improbable::EntityAcl>(data->GetUnderlying());
	return this;
}

UEntityTemplate* UEntityTemplate::AddMetadataComponent(UMetadataData* data)
{
    Underlying.Add<improbable::Metadata>(data->GetUnderlying());
	return this;
}

UEntityTemplate* UEntityTemplate::AddPositionComponent(UPositionData* data)
{
    Underlying.Add<improbable::Position>(data->GetUnderlying());
	return this;
}

UEntityTemplate* UEntityTemplate::AddPersistenceComponent(UPersistenceData* data)
{
    Underlying.Add<improbable::Persistence>(data->GetUnderlying());
	return this;
}

worker::Entity UEntityTemplate::GetUnderlying()
{
	return Underlying;
}
