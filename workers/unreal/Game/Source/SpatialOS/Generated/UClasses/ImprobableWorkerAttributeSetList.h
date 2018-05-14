// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "improbable/collections.h"
#include "UObject/NoExportTypes.h"

#include "WorkerAttributeSet.h"

#include "ImprobableWorkerAttributeSetList.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UImprobableWorkerAttributeSetList : public UObject
{
    GENERATED_BODY()

  public:
    UImprobableWorkerAttributeSetList();
    UImprobableWorkerAttributeSetList* Init(const worker::List<improbable::WorkerAttributeSet>& underlying);

    UFUNCTION(BlueprintCallable, Category = "ImprobableWorkerAttributeSetList")
    UImprobableWorkerAttributeSetList* Add(UWorkerAttributeSet* value);

    UFUNCTION(BlueprintPure, Category = "ImprobableWorkerAttributeSetList")
    UWorkerAttributeSet* Get(int pos);

    UFUNCTION(BlueprintCallable, Category = "ImprobableWorkerAttributeSetList")
    UImprobableWorkerAttributeSetList* Clear();

    UFUNCTION(BlueprintPure, Category = "ImprobableWorkerAttributeSetList")
    bool IsEmpty();

	UFUNCTION(BlueprintPure, Category = "ImprobableWorkerAttributeSetList")
    int Size();

	bool operator==(const worker::List<improbable::WorkerAttributeSet>& OtherUnderlying) const;
	bool operator!=(const worker::List<improbable::WorkerAttributeSet>& OtherUnderlying) const;	

    worker::List<improbable::WorkerAttributeSet> GetUnderlying();

  private:
    worker::List<improbable::WorkerAttributeSet> Underlying;
};
