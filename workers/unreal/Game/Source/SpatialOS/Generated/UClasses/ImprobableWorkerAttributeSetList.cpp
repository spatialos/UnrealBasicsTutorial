#include "ImprobableWorkerAttributeSetList.h"
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

UImprobableWorkerAttributeSetList::UImprobableWorkerAttributeSetList()
{
}

UImprobableWorkerAttributeSetList* UImprobableWorkerAttributeSetList::Init(const worker::List<improbable::WorkerAttributeSet>& underlying)
{
	Underlying = worker::List<improbable::WorkerAttributeSet>(underlying);
	return this;
}

UImprobableWorkerAttributeSetList* UImprobableWorkerAttributeSetList::Add(UWorkerAttributeSet* value)
{
	auto underlyingValue = value->GetUnderlying();
	Underlying.emplace_back(underlyingValue);
	return this;
}

UWorkerAttributeSet* UImprobableWorkerAttributeSetList::Get(int pos)
{
	return NewObject<UWorkerAttributeSet>()->Init((Underlying)[pos]);
}

UImprobableWorkerAttributeSetList* UImprobableWorkerAttributeSetList::Clear()
{
	Underlying.clear();
	return this;
}

bool UImprobableWorkerAttributeSetList::IsEmpty()
{
	return Underlying.empty();
}

int UImprobableWorkerAttributeSetList::Size()
{
	return static_cast<int>(Underlying.size());
}

bool UImprobableWorkerAttributeSetList::operator==(const worker::List<improbable::WorkerAttributeSet>& OtherUnderlying) const
{
	return Underlying == OtherUnderlying;
}

bool UImprobableWorkerAttributeSetList::operator!=(const worker::List<improbable::WorkerAttributeSet>& OtherUnderlying) const
{
	return Underlying != OtherUnderlying;
}

worker::List<improbable::WorkerAttributeSet> UImprobableWorkerAttributeSetList::GetUnderlying()
{
	return Underlying;
}
