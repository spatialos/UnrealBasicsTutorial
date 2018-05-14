// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "EntityAclData.h"

UEntityAclData::UEntityAclData()
{
	Underlying.Reset(new improbable::EntityAclData(improbable::WorkerRequirementSet(worker::List<improbable::WorkerAttributeSet>()), worker::Map<std::uint32_t, improbable::WorkerRequirementSet>()));
}

UEntityAclData* UEntityAclData::Init(const improbable::EntityAclData& underlying)
{
    Underlying.Reset(new improbable::EntityAclData(underlying));
	return this;
}

UWorkerRequirementSet* UEntityAclData::GetReadAcl()
{
    return NewObject<UWorkerRequirementSet>()->Init(Underlying->read_acl());
}
UEntityAclData* UEntityAclData::SetReadAcl(UWorkerRequirementSet* read_acl)
{
    Underlying->set_read_acl(read_acl->GetUnderlying());
	return this;
}

UStdUint32TToImprobableWorkerRequirementSetMap* UEntityAclData::GetComponentWriteAcl()
{
    return NewObject<UStdUint32TToImprobableWorkerRequirementSetMap>()->Init(Underlying->component_write_acl());
}
UEntityAclData* UEntityAclData::SetComponentWriteAcl(UStdUint32TToImprobableWorkerRequirementSetMap* component_write_acl)
{
    Underlying->set_component_write_acl(component_write_acl->GetUnderlying());
	return this;
}


improbable::EntityAclData UEntityAclData::GetUnderlying()
{
	return *Underlying.Get();
}
