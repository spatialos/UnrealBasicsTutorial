// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/standard_library.h"

#include "improbable/standard_library.h"
#include "SpatialOSConversionFunctionLibrary.h"
#include "PositionData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UPositionData : public UObject
{
    GENERATED_BODY()

  public:
    UPositionData();
    UPositionData* Init(const improbable::PositionData& underlying);

    UFUNCTION(BlueprintPure, Category = "PositionData")
    FVector GetCoords();
	UFUNCTION(BlueprintCallable, Category = "PositionData")
    UPositionData* SetCoords(FVector coords);


	improbable::PositionData GetUnderlying();

  private:
    TUniquePtr<improbable::PositionData> Underlying;
};

