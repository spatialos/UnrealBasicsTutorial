// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "SpawnerData.h"

USpawnerData::USpawnerData()
{
	Underlying.Reset(new improbable::spawner::SpawnerData());
}

USpawnerData* USpawnerData::Init(const improbable::spawner::SpawnerData& underlying)
{
    Underlying.Reset(new improbable::spawner::SpawnerData(underlying));
	return this;
}


improbable::spawner::SpawnerData USpawnerData::GetUnderlying()
{
	return *Underlying.Get();
}
