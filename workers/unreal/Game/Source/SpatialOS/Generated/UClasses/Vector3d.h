// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/vector3.h"

#include "Vector3d.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UVector3d : public UObject
{
    GENERATED_BODY()

  public:
    UVector3d();
    UVector3d* Init(const improbable::Vector3d& underlying);

    UFUNCTION(BlueprintPure, Category = "Vector3d")
    float GetX();
	UFUNCTION(BlueprintCallable, Category = "Vector3d")
    UVector3d* SetX(float x);

    UFUNCTION(BlueprintPure, Category = "Vector3d")
    float GetY();
	UFUNCTION(BlueprintCallable, Category = "Vector3d")
    UVector3d* SetY(float y);

    UFUNCTION(BlueprintPure, Category = "Vector3d")
    float GetZ();
	UFUNCTION(BlueprintCallable, Category = "Vector3d")
    UVector3d* SetZ(float z);


	improbable::Vector3d GetUnderlying();

  private:
    TUniquePtr<improbable::Vector3d> Underlying;
};

