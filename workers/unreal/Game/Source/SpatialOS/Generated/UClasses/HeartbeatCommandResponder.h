// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "improbable/player/heartbeat.h"

#include "HeartbeatResponse.h"

#include "CoreMinimal.h"
#include "SpatialOSWorkerTypes.h"
#include "UObject/NoExportTypes.h"
#include "HeartbeatCommandResponder.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UHeartbeatCommandResponder : public UObject
{
    GENERATED_BODY()

  public:
    UHeartbeatCommandResponder();
	UHeartbeatCommandResponder* Init(
        const TWeakPtr<SpatialOSConnection>& InConnection,
        worker::RequestId<
            worker::IncomingCommandRequest<improbable::player::HeartbeatReceiver::Commands::Heartbeat>
		> InRequestId,
        UHeartbeatRequest* InRequest, 
		const std::string& InCallerWorkerId
	);

    UFUNCTION(BlueprintPure, Category = "HeartbeatReceiverComponent")
    UHeartbeatRequest* GetRequest();

	UFUNCTION(BlueprintPure, Category = "HeartbeatReceiverComponent")
    FString GetCallerWorkerId();

    UFUNCTION(BlueprintCallable, Category = "HeartbeatReceiverComponent")
    void SendResponse(UHeartbeatResponse* response);

  private:

    TWeakPtr<SpatialOSConnection> Connection;

    worker::RequestId<worker::IncomingCommandRequest<improbable::player::HeartbeatReceiver::Commands::Heartbeat>>
        RequestId;

	UPROPERTY()
    UHeartbeatRequest* Request;

	FString CallerWorkerId;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHeartbeatCommand, UHeartbeatCommandResponder*, responder);
