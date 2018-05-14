// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "MetadataComponentUpdate.h"

improbable::Metadata::Update UMetadataComponentUpdate::DefaultUnderlying = improbable::Metadata::Update();

UMetadataComponentUpdate::UMetadataComponentUpdate()
{
}

UMetadataComponentUpdate* UMetadataComponentUpdate::Init(const improbable::Metadata::Update& underlying)
{
	return InitInternal(underlying);
}

UMetadataComponentUpdate* UMetadataComponentUpdate::Reset()
{
	return ResetInternal();
}

bool UMetadataComponentUpdate::HasEntityType()
{
    return !Underlying.entity_type().empty();
}

FString UMetadataComponentUpdate::GetEntityType()
{
	EntityType = FString((*(Underlying.entity_type().data())).c_str());
    return EntityType;
}

UMetadataComponentUpdate* UMetadataComponentUpdate::SetEntityType(FString newValue)
{
    return SetEntityTypeInternal(newValue);
}

const improbable::Metadata::Update UMetadataComponentUpdate::GetUnderlying()
{
    return GetUnderlyingInternal();
}

UMetadataComponentUpdate* UMetadataComponentUpdate::InitInternal(const improbable::Metadata::Update& underlying)
{
    Underlying = improbable::Metadata::Update(underlying);
	return this;
}

UMetadataComponentUpdate* UMetadataComponentUpdate::ResetInternal()
{
	return InitInternal(DefaultUnderlying);
}

UMetadataComponentUpdate* UMetadataComponentUpdate::SetEntityTypeInternal(FString newValue)
{
    Underlying.set_entity_type(TCHAR_TO_UTF8(*newValue));
	return this;
}

const improbable::Metadata::Update UMetadataComponentUpdate::GetUnderlyingInternal()
{
    return Underlying;
}
