// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/standard_library.h"

#include "StdStringList.h"
#include <string>
#include "WorkerAttributeSet.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UWorkerAttributeSet : public UObject
{
    GENERATED_BODY()

  public:
    UWorkerAttributeSet();
    UWorkerAttributeSet* Init(const improbable::WorkerAttributeSet& underlying);

    UFUNCTION(BlueprintPure, Category = "WorkerAttributeSet")
    UStdStringList* GetAttribute();
	UFUNCTION(BlueprintCallable, Category = "WorkerAttributeSet")
    UWorkerAttributeSet* SetAttribute(UStdStringList* attribute);


	improbable::WorkerAttributeSet GetUnderlying();

  private:
    TUniquePtr<improbable::WorkerAttributeSet> Underlying;
};

