// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/standard_library.h"

#include "Coordinates.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UCoordinates : public UObject
{
    GENERATED_BODY()

  public:
    UCoordinates();
    UCoordinates* Init(const improbable::Coordinates& underlying);

    UFUNCTION(BlueprintPure, Category = "Coordinates")
    float GetX();
	UFUNCTION(BlueprintCallable, Category = "Coordinates")
    UCoordinates* SetX(float x);

    UFUNCTION(BlueprintPure, Category = "Coordinates")
    float GetY();
	UFUNCTION(BlueprintCallable, Category = "Coordinates")
    UCoordinates* SetY(float y);

    UFUNCTION(BlueprintPure, Category = "Coordinates")
    float GetZ();
	UFUNCTION(BlueprintCallable, Category = "Coordinates")
    UCoordinates* SetZ(float z);


	improbable::Coordinates GetUnderlying();

  private:
    TUniquePtr<improbable::Coordinates> Underlying;
};

