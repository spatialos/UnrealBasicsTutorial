// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/spawner/spawner.h"

#include "SpawnerData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API USpawnerData : public UObject
{
    GENERATED_BODY()

  public:
    USpawnerData();
    USpawnerData* Init(const improbable::spawner::SpawnerData& underlying);


	improbable::spawner::SpawnerData GetUnderlying();

  private:
    TUniquePtr<improbable::spawner::SpawnerData> Underlying;
};

