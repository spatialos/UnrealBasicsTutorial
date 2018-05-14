// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "SpatialOsComponent.h"
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "HeartbeatReceiverComponentUpdate.h"
#include "HeartbeatReceiverAddComponentOp.h"
#include "ComponentId.h"
#include "SpatialOSViewTypes.h"
#include "SpatialOSWorkerTypes.h"
#include "improbable/player/heartbeat.h"

#include "HeartbeatCommandResponder.h"


#include "HeartbeatReceiverComponent.generated.h"

class UCallbackDispatcher;
class UComponentUpdateOpWrapperBase;

USTRUCT()
struct FHeartbeatReceiverComponentSnapshot
{
	GENERATED_BODY()

	FHeartbeatReceiverComponentSnapshot()
	{
	}

};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPATIALOS_API UHeartbeatReceiverComponent : public USpatialOsComponent
{
    GENERATED_BODY()

public:
    UHeartbeatReceiverComponent();
	virtual ~UHeartbeatReceiverComponent() override = default;

    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "HeartbeatReceiverComponent")
    FComponentId GetComponentId();

    const static worker::ComponentId ComponentId;

    void Init(const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView, worker::EntityId InEntityId, UCallbackDispatcher* InCallbackDispatcher) override;

	void Disable(const worker::EntityId InEntityId, UCallbackDispatcher* CallbackDispatcher);

	void ApplyInitialState(const UAddComponentOpWrapperBase& Op) override;

	DEPRECATED(12.1, "Please use TriggerAutomaticComponentUpdate.")
	void ReplicateChanges(float DeltaSeconds) override;

	void TriggerAutomaticComponentUpdate(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "HeartbeatReceiverComponent")
	void TriggerManualComponentUpdate();


    UPROPERTY(BlueprintAssignable, Category = "HeartbeatReceiverComponent")
    FHeartbeatCommand OnHeartbeatCommandRequest;

	DEPRECATED(12.1, "This function is deprecated, the component updates are now sent automatically. Use MaxUpdatesPerSecond property to control the update frequency, or set it to 0 and use TriggerManualComponentUpdate for more control.")
    UFUNCTION(BlueprintCallable, Category = "HeartbeatReceiverComponent", meta=(DeprecatedFunction, DeprecationMessage="This function is deprecated, the component updates are now sent automatically. Use MaxUpdatesPerSecond property to control the update frequency, or set it to 0 and use TriggerManualComponentUpdate for more control."))
    void SendComponentUpdate(UHeartbeatReceiverComponentUpdate* update);

    UPROPERTY(BlueprintAssignable, Category = "HeartbeatReceiverComponent")
    FSpatialComponentUpdated OnComponentUpdate;



private:
	void GenerateSnapshot();

	UPROPERTY()
	UHeartbeatReceiverComponentUpdate* ComponentUpdater;


	FHeartbeatReceiverComponentSnapshot* Snapshot;

    void OnComponentUpdateDispatcherCallback(UComponentUpdateOpWrapperBase& Op);

	void OnAuthorityChangeDispatcherCallback(const worker::AuthorityChangeOp& Op) override;

	void ReplicateChangesInternal();
	void SendComponentUpdateInternal(UHeartbeatReceiverComponentUpdate* update);
    void ApplyComponentUpdate(const improbable::player::HeartbeatReceiver::Update& update);
	void NotifyUpdate(const improbable::player::HeartbeatReceiver::Update& update);


    void OnHeartbeatCommandRequestDispatcherCallback(
        const worker::CommandRequestOp<improbable::player::HeartbeatReceiver::Commands::Heartbeat>& op);

};
