// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "WorkerAttributeSet.h"

UWorkerAttributeSet::UWorkerAttributeSet()
{
	Underlying.Reset(new improbable::WorkerAttributeSet(worker::List<std::string>()));
}

UWorkerAttributeSet* UWorkerAttributeSet::Init(const improbable::WorkerAttributeSet& underlying)
{
    Underlying.Reset(new improbable::WorkerAttributeSet(underlying));
	return this;
}

UStdStringList* UWorkerAttributeSet::GetAttribute()
{
    return NewObject<UStdStringList>()->Init(Underlying->attribute());
}
UWorkerAttributeSet* UWorkerAttributeSet::SetAttribute(UStdStringList* attribute)
{
    Underlying->set_attribute(attribute->GetUnderlying());
	return this;
}


improbable::WorkerAttributeSet UWorkerAttributeSet::GetUnderlying()
{
	return *Underlying.Get();
}
