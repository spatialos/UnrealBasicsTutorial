// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "SpatialOsComponent.h"
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "PositionComponentUpdate.h"
#include "PositionAddComponentOp.h"
#include "ComponentId.h"
#include "SpatialOSViewTypes.h"
#include "SpatialOSWorkerTypes.h"
#include "improbable/standard_library.h"

#include "improbable/standard_library.h"
#include "SpatialOSConversionFunctionLibrary.h"


#include "PositionComponent.generated.h"

class UCallbackDispatcher;
class UComponentUpdateOpWrapperBase;

USTRUCT()
struct FPositionComponentSnapshot
{
	GENERATED_BODY()

	FPositionComponentSnapshot()
	{
	}

	FVector Coords;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPATIALOS_API UPositionComponent : public USpatialOsComponent
{
    GENERATED_BODY()

public:
    UPositionComponent();
	virtual ~UPositionComponent() override = default;

    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "PositionComponent")
    FComponentId GetComponentId();

    const static worker::ComponentId ComponentId;

    void Init(const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView, worker::EntityId InEntityId, UCallbackDispatcher* InCallbackDispatcher) override;

	void Disable(const worker::EntityId InEntityId, UCallbackDispatcher* CallbackDispatcher);

	void ApplyInitialState(const UAddComponentOpWrapperBase& Op) override;

	DEPRECATED(12.1, "Please use TriggerAutomaticComponentUpdate.")
	void ReplicateChanges(float DeltaSeconds) override;

	void TriggerAutomaticComponentUpdate(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "PositionComponent")
	void TriggerManualComponentUpdate();

    UPROPERTY(BlueprintAssignable, Category = "PositionComponent")
    FSpatialComponentUpdated OnCoordsUpdate;



	DEPRECATED(12.1, "This function is deprecated, the component updates are now sent automatically. Use MaxUpdatesPerSecond property to control the update frequency, or set it to 0 and use TriggerManualComponentUpdate for more control.")
    UFUNCTION(BlueprintCallable, Category = "PositionComponent", meta=(DeprecatedFunction, DeprecationMessage="This function is deprecated, the component updates are now sent automatically. Use MaxUpdatesPerSecond property to control the update frequency, or set it to 0 and use TriggerManualComponentUpdate for more control."))
    void SendComponentUpdate(UPositionComponentUpdate* update);

    UPROPERTY(BlueprintAssignable, Category = "PositionComponent")
    FSpatialComponentUpdated OnComponentUpdate;

	DEPRECATED(12.0, "This function is deprecated, access the Coords property directly.")
    UFUNCTION(BlueprintPure, Category = "PositionComponent", meta=(DeprecatedFunction, DeprecationMessage="This function is deprecated, access the Coords property directly."))
    FVector GetCoords();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Coords;

private:
	void GenerateSnapshot();

	UPROPERTY()
	UPositionComponentUpdate* ComponentUpdater;


	FPositionComponentSnapshot* Snapshot;

    void OnComponentUpdateDispatcherCallback(UComponentUpdateOpWrapperBase& Op);

	void OnAuthorityChangeDispatcherCallback(const worker::AuthorityChangeOp& Op) override;

	void ReplicateChangesInternal();
	void SendComponentUpdateInternal(UPositionComponentUpdate* update);
    void ApplyComponentUpdate(const improbable::Position::Update& update);
	void NotifyUpdate(const improbable::Position::Update& update);

};
