// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/standard_library.h"

#include "PersistenceData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UPersistenceData : public UObject
{
    GENERATED_BODY()

  public:
    UPersistenceData();
    UPersistenceData* Init(const improbable::PersistenceData& underlying);


	improbable::PersistenceData GetUnderlying();

  private:
    TUniquePtr<improbable::PersistenceData> Underlying;
};

