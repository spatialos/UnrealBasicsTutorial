// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "WorkerRequirementSet.h"

UWorkerRequirementSet::UWorkerRequirementSet()
{
	Underlying.Reset(new improbable::WorkerRequirementSet(worker::List<improbable::WorkerAttributeSet>()));
}

UWorkerRequirementSet* UWorkerRequirementSet::Init(const improbable::WorkerRequirementSet& underlying)
{
    Underlying.Reset(new improbable::WorkerRequirementSet(underlying));
	return this;
}

UImprobableWorkerAttributeSetList* UWorkerRequirementSet::GetAttributeSet()
{
    return NewObject<UImprobableWorkerAttributeSetList>()->Init(Underlying->attribute_set());
}
UWorkerRequirementSet* UWorkerRequirementSet::SetAttributeSet(UImprobableWorkerAttributeSetList* attribute_set)
{
    Underlying->set_attribute_set(attribute_set->GetUnderlying());
	return this;
}


improbable::WorkerRequirementSet UWorkerRequirementSet::GetUnderlying()
{
	return *Underlying.Get();
}
