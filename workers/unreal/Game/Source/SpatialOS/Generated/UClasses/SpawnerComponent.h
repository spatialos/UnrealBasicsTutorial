// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "SpatialOsComponent.h"
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "SpawnerComponentUpdate.h"
#include "SpawnerAddComponentOp.h"
#include "ComponentId.h"
#include "SpatialOSViewTypes.h"
#include "SpatialOSWorkerTypes.h"
#include "improbable/spawner/spawner.h"

#include "SpawnPlayerCommandResponder.h"


#include "SpawnerComponent.generated.h"

class UCallbackDispatcher;
class UComponentUpdateOpWrapperBase;

USTRUCT()
struct FSpawnerComponentSnapshot
{
	GENERATED_BODY()

	FSpawnerComponentSnapshot()
	{
	}

};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPATIALOS_API USpawnerComponent : public USpatialOsComponent
{
    GENERATED_BODY()

public:
    USpawnerComponent();
	virtual ~USpawnerComponent() override = default;

    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "SpawnerComponent")
    FComponentId GetComponentId();

    const static worker::ComponentId ComponentId;

    void Init(const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView, worker::EntityId InEntityId, UCallbackDispatcher* InCallbackDispatcher) override;

	void Disable(const worker::EntityId InEntityId, UCallbackDispatcher* CallbackDispatcher);

	void ApplyInitialState(const UAddComponentOpWrapperBase& Op) override;

	DEPRECATED(12.1, "Please use TriggerAutomaticComponentUpdate.")
	void ReplicateChanges(float DeltaSeconds) override;

	void TriggerAutomaticComponentUpdate(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "SpawnerComponent")
	void TriggerManualComponentUpdate();


    UPROPERTY(BlueprintAssignable, Category = "SpawnerComponent")
    FSpawnPlayerCommand OnSpawnPlayerCommandRequest;

	DEPRECATED(12.1, "This function is deprecated, the component updates are now sent automatically. Use MaxUpdatesPerSecond property to control the update frequency, or set it to 0 and use TriggerManualComponentUpdate for more control.")
    UFUNCTION(BlueprintCallable, Category = "SpawnerComponent", meta=(DeprecatedFunction, DeprecationMessage="This function is deprecated, the component updates are now sent automatically. Use MaxUpdatesPerSecond property to control the update frequency, or set it to 0 and use TriggerManualComponentUpdate for more control."))
    void SendComponentUpdate(USpawnerComponentUpdate* update);

    UPROPERTY(BlueprintAssignable, Category = "SpawnerComponent")
    FSpatialComponentUpdated OnComponentUpdate;



private:
	void GenerateSnapshot();

	UPROPERTY()
	USpawnerComponentUpdate* ComponentUpdater;


	FSpawnerComponentSnapshot* Snapshot;

    void OnComponentUpdateDispatcherCallback(UComponentUpdateOpWrapperBase& Op);

	void OnAuthorityChangeDispatcherCallback(const worker::AuthorityChangeOp& Op) override;

	void ReplicateChangesInternal();
	void SendComponentUpdateInternal(USpawnerComponentUpdate* update);
    void ApplyComponentUpdate(const improbable::spawner::Spawner::Update& update);
	void NotifyUpdate(const improbable::spawner::Spawner::Update& update);


    void OnSpawnPlayerCommandRequestDispatcherCallback(
        const worker::CommandRequestOp<improbable::spawner::Spawner::Commands::SpawnPlayer>& op);

};
