// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/standard_library.h"

#include "ImprobableWorkerAttributeSetList.h"
#include "WorkerAttributeSet.h"
#include "WorkerRequirementSet.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UWorkerRequirementSet : public UObject
{
    GENERATED_BODY()

  public:
    UWorkerRequirementSet();
    UWorkerRequirementSet* Init(const improbable::WorkerRequirementSet& underlying);

    UFUNCTION(BlueprintPure, Category = "WorkerRequirementSet")
    UImprobableWorkerAttributeSetList* GetAttributeSet();
	UFUNCTION(BlueprintCallable, Category = "WorkerRequirementSet")
    UWorkerRequirementSet* SetAttributeSet(UImprobableWorkerAttributeSetList* attribute_set);


	improbable::WorkerRequirementSet GetUnderlying();

  private:
    TUniquePtr<improbable::WorkerRequirementSet> Underlying;
};

