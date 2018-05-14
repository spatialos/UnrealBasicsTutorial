#include "StdUint32TToImprobableWorkerRequirementSetMap.h"
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

UStdUint32TToImprobableWorkerRequirementSetMap::UStdUint32TToImprobableWorkerRequirementSetMap()
{
}

UStdUint32TToImprobableWorkerRequirementSetMap* UStdUint32TToImprobableWorkerRequirementSetMap::Init(const worker::Map<std::uint32_t, improbable::WorkerRequirementSet>& underlying)
{
	Underlying = worker::Map<std::uint32_t, improbable::WorkerRequirementSet>(underlying);
	return this;
}

UStdUint32TToImprobableWorkerRequirementSetMap* UStdUint32TToImprobableWorkerRequirementSetMap::Emplace(int key, UWorkerRequirementSet* value)
{
	std::uint32_t underlyingKey = static_cast<std::uint32_t>(key);
	auto underlyingValue = value->GetUnderlying();
	Underlying.emplace(underlyingKey, underlyingValue);
	return this;
}

UStdUint32TToImprobableWorkerRequirementSetMap* UStdUint32TToImprobableWorkerRequirementSetMap::Remove(int key)
{
	std::uint32_t underlyingKey = static_cast<std::uint32_t>(key);
	Underlying.erase(underlyingKey);
	return this;
}

bool UStdUint32TToImprobableWorkerRequirementSetMap::Contains(int key)
{
	std::uint32_t underlyingKey = static_cast<std::uint32_t>(key);
	return Underlying.find(underlyingKey) != Underlying.end();
}

UWorkerRequirementSet* UStdUint32TToImprobableWorkerRequirementSetMap::Get(int key)
{
	std::uint32_t underlyingKey = static_cast<std::uint32_t>(key);
	auto iterator = Underlying.find(underlyingKey);
	return NewObject<UWorkerRequirementSet>()->Init(iterator->second);
}

UStdUint32TToImprobableWorkerRequirementSetMap* UStdUint32TToImprobableWorkerRequirementSetMap::Clear()
{
	Underlying.clear();
	return this;
}

bool UStdUint32TToImprobableWorkerRequirementSetMap::IsEmpty()
{
	return Underlying.empty();
}

bool UStdUint32TToImprobableWorkerRequirementSetMap::operator==(const worker::Map<std::uint32_t, improbable::WorkerRequirementSet>& OtherUnderlying) const
{
	return Underlying == OtherUnderlying;
}

bool UStdUint32TToImprobableWorkerRequirementSetMap::operator!=(const worker::Map<std::uint32_t, improbable::WorkerRequirementSet>& OtherUnderlying) const
{
	return Underlying != OtherUnderlying;
}

worker::Map<std::uint32_t, improbable::WorkerRequirementSet> UStdUint32TToImprobableWorkerRequirementSetMap::GetUnderlying()
{
	return Underlying;
}