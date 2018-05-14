// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/standard_library.h"

#include <string>
#include "MetadataData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UMetadataData : public UObject
{
    GENERATED_BODY()

  public:
    UMetadataData();
    UMetadataData* Init(const improbable::MetadataData& underlying);

    UFUNCTION(BlueprintPure, Category = "MetadataData")
    FString GetEntityType();
	UFUNCTION(BlueprintCallable, Category = "MetadataData")
    UMetadataData* SetEntityType(FString entity_type);


	improbable::MetadataData GetUnderlying();

  private:
    TUniquePtr<improbable::MetadataData> Underlying;
};

