// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "EntityAclComponentUpdate.h"

improbable::EntityAcl::Update UEntityAclComponentUpdate::DefaultUnderlying = improbable::EntityAcl::Update();

UEntityAclComponentUpdate::UEntityAclComponentUpdate()
: ReadAcl(nullptr)
, ComponentWriteAcl(nullptr)
{
}

UEntityAclComponentUpdate* UEntityAclComponentUpdate::Init(const improbable::EntityAcl::Update& underlying)
{
	return InitInternal(underlying);
}

UEntityAclComponentUpdate* UEntityAclComponentUpdate::Reset()
{
	return ResetInternal();
}

bool UEntityAclComponentUpdate::HasReadAcl()
{
    return !Underlying.read_acl().empty();
}

UWorkerRequirementSet* UEntityAclComponentUpdate::GetReadAcl()
{
	if (ReadAcl == nullptr) { ReadAcl = NewObject<UWorkerRequirementSet>(this); } ReadAcl->Init((*(Underlying.read_acl().data())));
    return ReadAcl;
}

UEntityAclComponentUpdate* UEntityAclComponentUpdate::SetReadAcl(UWorkerRequirementSet* newValue)
{
    return SetReadAclInternal(newValue);
}

bool UEntityAclComponentUpdate::HasComponentWriteAcl()
{
    return !Underlying.component_write_acl().empty();
}

UStdUint32TToImprobableWorkerRequirementSetMap* UEntityAclComponentUpdate::GetComponentWriteAcl()
{
	if (ComponentWriteAcl == nullptr) { ComponentWriteAcl = NewObject<UStdUint32TToImprobableWorkerRequirementSetMap>(this); } ComponentWriteAcl->Init((*(Underlying.component_write_acl().data())));
    return ComponentWriteAcl;
}

UEntityAclComponentUpdate* UEntityAclComponentUpdate::SetComponentWriteAcl(UStdUint32TToImprobableWorkerRequirementSetMap* newValue)
{
    return SetComponentWriteAclInternal(newValue);
}

const improbable::EntityAcl::Update UEntityAclComponentUpdate::GetUnderlying()
{
    return GetUnderlyingInternal();
}

UEntityAclComponentUpdate* UEntityAclComponentUpdate::InitInternal(const improbable::EntityAcl::Update& underlying)
{
    Underlying = improbable::EntityAcl::Update(underlying);
	return this;
}

UEntityAclComponentUpdate* UEntityAclComponentUpdate::ResetInternal()
{
	return InitInternal(DefaultUnderlying);
}

UEntityAclComponentUpdate* UEntityAclComponentUpdate::SetReadAclInternal(UWorkerRequirementSet* newValue)
{
    Underlying.set_read_acl(newValue->GetUnderlying());
	return this;
}

UEntityAclComponentUpdate* UEntityAclComponentUpdate::SetComponentWriteAclInternal(UStdUint32TToImprobableWorkerRequirementSetMap* newValue)
{
    Underlying.set_component_write_acl(newValue->GetUnderlying());
	return this;
}

const improbable::EntityAcl::Update UEntityAclComponentUpdate::GetUnderlyingInternal()
{
    return Underlying;
}
