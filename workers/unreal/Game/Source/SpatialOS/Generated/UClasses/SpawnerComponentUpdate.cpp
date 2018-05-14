// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "SpawnerComponentUpdate.h"

improbable::spawner::Spawner::Update USpawnerComponentUpdate::DefaultUnderlying = improbable::spawner::Spawner::Update();

USpawnerComponentUpdate::USpawnerComponentUpdate()
{
}

USpawnerComponentUpdate* USpawnerComponentUpdate::Init(const improbable::spawner::Spawner::Update& underlying)
{
	return InitInternal(underlying);
}

USpawnerComponentUpdate* USpawnerComponentUpdate::Reset()
{
	return ResetInternal();
}

const improbable::spawner::Spawner::Update USpawnerComponentUpdate::GetUnderlying()
{
    return GetUnderlyingInternal();
}

USpawnerComponentUpdate* USpawnerComponentUpdate::InitInternal(const improbable::spawner::Spawner::Update& underlying)
{
    Underlying = improbable::spawner::Spawner::Update(underlying);
	return this;
}

USpawnerComponentUpdate* USpawnerComponentUpdate::ResetInternal()
{
	return InitInternal(DefaultUnderlying);
}

const improbable::spawner::Spawner::Update USpawnerComponentUpdate::GetUnderlyingInternal()
{
    return Underlying;
}
