// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "SpatialOsComponent.h"
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "HeartbeatSenderComponentUpdate.h"
#include "HeartbeatSenderAddComponentOp.h"
#include "ComponentId.h"
#include "SpatialOSViewTypes.h"
#include "SpatialOSWorkerTypes.h"
#include "improbable/player/heartbeat.h"



#include "HeartbeatSenderComponent.generated.h"

class UCallbackDispatcher;
class UComponentUpdateOpWrapperBase;

USTRUCT()
struct FHeartbeatSenderComponentSnapshot
{
	GENERATED_BODY()

	FHeartbeatSenderComponentSnapshot()
	{
	}

};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPATIALOS_API UHeartbeatSenderComponent : public USpatialOsComponent
{
    GENERATED_BODY()

public:
    UHeartbeatSenderComponent();
	virtual ~UHeartbeatSenderComponent() override = default;

    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "HeartbeatSenderComponent")
    FComponentId GetComponentId();

    const static worker::ComponentId ComponentId;

    void Init(const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView, worker::EntityId InEntityId, UCallbackDispatcher* InCallbackDispatcher) override;

	void Disable(const worker::EntityId InEntityId, UCallbackDispatcher* CallbackDispatcher);

	void ApplyInitialState(const UAddComponentOpWrapperBase& Op) override;

	DEPRECATED(12.1, "Please use TriggerAutomaticComponentUpdate.")
	void ReplicateChanges(float DeltaSeconds) override;

	void TriggerAutomaticComponentUpdate(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "HeartbeatSenderComponent")
	void TriggerManualComponentUpdate();



	DEPRECATED(12.1, "This function is deprecated, the component updates are now sent automatically. Use MaxUpdatesPerSecond property to control the update frequency, or set it to 0 and use TriggerManualComponentUpdate for more control.")
    UFUNCTION(BlueprintCallable, Category = "HeartbeatSenderComponent", meta=(DeprecatedFunction, DeprecationMessage="This function is deprecated, the component updates are now sent automatically. Use MaxUpdatesPerSecond property to control the update frequency, or set it to 0 and use TriggerManualComponentUpdate for more control."))
    void SendComponentUpdate(UHeartbeatSenderComponentUpdate* update);

    UPROPERTY(BlueprintAssignable, Category = "HeartbeatSenderComponent")
    FSpatialComponentUpdated OnComponentUpdate;



private:
	void GenerateSnapshot();

	UPROPERTY()
	UHeartbeatSenderComponentUpdate* ComponentUpdater;


	FHeartbeatSenderComponentSnapshot* Snapshot;

    void OnComponentUpdateDispatcherCallback(UComponentUpdateOpWrapperBase& Op);

	void OnAuthorityChangeDispatcherCallback(const worker::AuthorityChangeOp& Op) override;

	void ReplicateChangesInternal();
	void SendComponentUpdateInternal(UHeartbeatSenderComponentUpdate* update);
    void ApplyComponentUpdate(const improbable::player::HeartbeatSender::Update& update);
	void NotifyUpdate(const improbable::player::HeartbeatSender::Update& update);

};
