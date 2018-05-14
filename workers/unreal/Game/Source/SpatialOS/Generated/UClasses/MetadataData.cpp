// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "MetadataData.h"

UMetadataData::UMetadataData()
{
	Underlying.Reset(new improbable::MetadataData(""));
}

UMetadataData* UMetadataData::Init(const improbable::MetadataData& underlying)
{
    Underlying.Reset(new improbable::MetadataData(underlying));
	return this;
}

FString UMetadataData::GetEntityType()
{
    return FString(Underlying->entity_type().c_str());
}
UMetadataData* UMetadataData::SetEntityType(FString entity_type)
{
    Underlying->set_entity_type(TCHAR_TO_UTF8(*entity_type));
	return this;
}


improbable::MetadataData UMetadataData::GetUnderlying()
{
	return *Underlying.Get();
}
