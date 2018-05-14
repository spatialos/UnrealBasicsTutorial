// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "PersistenceData.h"

UPersistenceData::UPersistenceData()
{
	Underlying.Reset(new improbable::PersistenceData());
}

UPersistenceData* UPersistenceData::Init(const improbable::PersistenceData& underlying)
{
    Underlying.Reset(new improbable::PersistenceData(underlying));
	return this;
}


improbable::PersistenceData UPersistenceData::GetUnderlying()
{
	return *Underlying.Get();
}
