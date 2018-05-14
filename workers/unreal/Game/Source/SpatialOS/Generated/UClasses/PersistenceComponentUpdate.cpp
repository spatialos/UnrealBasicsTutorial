// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "PersistenceComponentUpdate.h"

improbable::Persistence::Update UPersistenceComponentUpdate::DefaultUnderlying = improbable::Persistence::Update();

UPersistenceComponentUpdate::UPersistenceComponentUpdate()
{
}

UPersistenceComponentUpdate* UPersistenceComponentUpdate::Init(const improbable::Persistence::Update& underlying)
{
	return InitInternal(underlying);
}

UPersistenceComponentUpdate* UPersistenceComponentUpdate::Reset()
{
	return ResetInternal();
}

const improbable::Persistence::Update UPersistenceComponentUpdate::GetUnderlying()
{
    return GetUnderlyingInternal();
}

UPersistenceComponentUpdate* UPersistenceComponentUpdate::InitInternal(const improbable::Persistence::Update& underlying)
{
    Underlying = improbable::Persistence::Update(underlying);
	return this;
}

UPersistenceComponentUpdate* UPersistenceComponentUpdate::ResetInternal()
{
	return InitInternal(DefaultUnderlying);
}

const improbable::Persistence::Update UPersistenceComponentUpdate::GetUnderlyingInternal()
{
    return Underlying;
}
