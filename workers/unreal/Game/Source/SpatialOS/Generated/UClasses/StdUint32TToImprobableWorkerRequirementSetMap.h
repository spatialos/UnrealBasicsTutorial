// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "improbable/collections.h"
#include "UObject/NoExportTypes.h"

#include "WorkerRequirementSet.h"


#include "StdUint32TToImprobableWorkerRequirementSetMap.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UStdUint32TToImprobableWorkerRequirementSetMap : public UObject
{
    GENERATED_BODY()

  public:
    UStdUint32TToImprobableWorkerRequirementSetMap();
    UStdUint32TToImprobableWorkerRequirementSetMap* Init(const worker::Map<std::uint32_t, improbable::WorkerRequirementSet>& underlying);

    UFUNCTION(BlueprintCallable, Category = "StdUint32TToImprobableWorkerRequirementSetMap")
    UStdUint32TToImprobableWorkerRequirementSetMap* Emplace(int key, UWorkerRequirementSet* value);

    UFUNCTION(BlueprintCallable, Category = "StdUint32TToImprobableWorkerRequirementSetMap")
    UStdUint32TToImprobableWorkerRequirementSetMap* Remove(int key);

    UFUNCTION(BlueprintPure, Category = "StdUint32TToImprobableWorkerRequirementSetMap")
    bool Contains(int key);

    UFUNCTION(BlueprintCallable, Category = "StdUint32TToImprobableWorkerRequirementSetMap")
    UWorkerRequirementSet* Get(int key);

    UFUNCTION(BlueprintCallable, Category = "StdUint32TToImprobableWorkerRequirementSetMap")
    UStdUint32TToImprobableWorkerRequirementSetMap* Clear();

    UFUNCTION(BlueprintPure, Category = "StdUint32TToImprobableWorkerRequirementSetMap")
    bool IsEmpty();

    worker::Map<std::uint32_t, improbable::WorkerRequirementSet> GetUnderlying();

	bool operator==(const worker::Map<std::uint32_t, improbable::WorkerRequirementSet>& OtherUnderlying) const;
	bool operator!=(const worker::Map<std::uint32_t, improbable::WorkerRequirementSet>& OtherUnderlying) const;

  private:
    worker::Map<std::uint32_t, improbable::WorkerRequirementSet> Underlying;
};
