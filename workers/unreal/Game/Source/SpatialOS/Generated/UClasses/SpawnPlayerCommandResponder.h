// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "improbable/spawner/spawner.h"

#include "SpawnPlayerResponse.h"

#include "CoreMinimal.h"
#include "SpatialOSWorkerTypes.h"
#include "UObject/NoExportTypes.h"
#include "SpawnPlayerCommandResponder.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API USpawnPlayerCommandResponder : public UObject
{
    GENERATED_BODY()

  public:
    USpawnPlayerCommandResponder();
	USpawnPlayerCommandResponder* Init(
        const TWeakPtr<SpatialOSConnection>& InConnection,
        worker::RequestId<
            worker::IncomingCommandRequest<improbable::spawner::Spawner::Commands::SpawnPlayer>
		> InRequestId,
        USpawnPlayerRequest* InRequest, 
		const std::string& InCallerWorkerId
	);

    UFUNCTION(BlueprintPure, Category = "SpawnerComponent")
    USpawnPlayerRequest* GetRequest();

	UFUNCTION(BlueprintPure, Category = "SpawnerComponent")
    FString GetCallerWorkerId();

    UFUNCTION(BlueprintCallable, Category = "SpawnerComponent")
    void SendResponse(USpawnPlayerResponse* response);

  private:

    TWeakPtr<SpatialOSConnection> Connection;

    worker::RequestId<worker::IncomingCommandRequest<improbable::spawner::Spawner::Commands::SpawnPlayer>>
        RequestId;

	UPROPERTY()
    USpawnPlayerRequest* Request;

	FString CallerWorkerId;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSpawnPlayerCommand, USpawnPlayerCommandResponder*, responder);
