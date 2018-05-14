// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/vector3.h"

#include "Vector3f.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UVector3f : public UObject
{
    GENERATED_BODY()

  public:
    UVector3f();
    UVector3f* Init(const improbable::Vector3f& underlying);

    UFUNCTION(BlueprintPure, Category = "Vector3f")
    float GetX();
	UFUNCTION(BlueprintCallable, Category = "Vector3f")
    UVector3f* SetX(float x);

    UFUNCTION(BlueprintPure, Category = "Vector3f")
    float GetY();
	UFUNCTION(BlueprintCallable, Category = "Vector3f")
    UVector3f* SetY(float y);

    UFUNCTION(BlueprintPure, Category = "Vector3f")
    float GetZ();
	UFUNCTION(BlueprintCallable, Category = "Vector3f")
    UVector3f* SetZ(float z);


	improbable::Vector3f GetUnderlying();

  private:
    TUniquePtr<improbable::Vector3f> Underlying;
};

