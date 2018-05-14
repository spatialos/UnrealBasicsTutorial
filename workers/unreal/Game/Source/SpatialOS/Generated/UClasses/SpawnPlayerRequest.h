// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/spawner/spawner.h"

#include "improbable/standard_library.h"
#include "SpatialOSConversionFunctionLibrary.h"
#include "SpawnPlayerRequest.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API USpawnPlayerRequest : public UObject
{
    GENERATED_BODY()

  public:
    USpawnPlayerRequest();
    USpawnPlayerRequest* Init(const improbable::spawner::SpawnPlayerRequest& underlying);

    UFUNCTION(BlueprintPure, Category = "SpawnPlayerRequest")
    FVector GetPosition();
	UFUNCTION(BlueprintCallable, Category = "SpawnPlayerRequest")
    USpawnPlayerRequest* SetPosition(FVector position);


	improbable::spawner::SpawnPlayerRequest GetUnderlying();

  private:
    TUniquePtr<improbable::spawner::SpawnPlayerRequest> Underlying;
};

