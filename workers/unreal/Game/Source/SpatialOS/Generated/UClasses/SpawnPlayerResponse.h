// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/spawner/spawner.h"

#include <string>
#include "EntityId.h"
#include "SpawnPlayerResponse.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API USpawnPlayerResponse : public UObject
{
    GENERATED_BODY()

  public:
    USpawnPlayerResponse();
    USpawnPlayerResponse* Init(const improbable::spawner::SpawnPlayerResponse& underlying);

    UFUNCTION(BlueprintPure, Category = "SpawnPlayerResponse")
    bool GetSuccess();
	UFUNCTION(BlueprintCallable, Category = "SpawnPlayerResponse")
    USpawnPlayerResponse* SetSuccess(bool success);

    UFUNCTION(BlueprintPure, Category = "SpawnPlayerResponse")
    FString GetErrorMessage();
	UFUNCTION(BlueprintCallable, Category = "SpawnPlayerResponse")
    USpawnPlayerResponse* SetErrorMessage(FString error_message);

    UFUNCTION(BlueprintPure, Category = "SpawnPlayerResponse")
    FEntityId GetCreatedEntityId();
	UFUNCTION(BlueprintCallable, Category = "SpawnPlayerResponse")
    USpawnPlayerResponse* SetCreatedEntityId(FEntityId created_entity_id);


	improbable::spawner::SpawnPlayerResponse GetUnderlying();

  private:
    TUniquePtr<improbable::spawner::SpawnPlayerResponse> Underlying;
};

