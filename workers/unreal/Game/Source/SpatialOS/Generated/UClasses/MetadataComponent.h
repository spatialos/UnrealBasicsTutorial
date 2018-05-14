// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "SpatialOsComponent.h"
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "MetadataComponentUpdate.h"
#include "MetadataAddComponentOp.h"
#include "ComponentId.h"
#include "SpatialOSViewTypes.h"
#include "SpatialOSWorkerTypes.h"
#include "improbable/standard_library.h"

#include <string>


#include "MetadataComponent.generated.h"

class UCallbackDispatcher;
class UComponentUpdateOpWrapperBase;

USTRUCT()
struct FMetadataComponentSnapshot
{
	GENERATED_BODY()

	FMetadataComponentSnapshot()
	{
	}

	FString EntityType;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPATIALOS_API UMetadataComponent : public USpatialOsComponent
{
    GENERATED_BODY()

public:
    UMetadataComponent();
	virtual ~UMetadataComponent() override = default;

    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "MetadataComponent")
    FComponentId GetComponentId();

    const static worker::ComponentId ComponentId;

    void Init(const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView, worker::EntityId InEntityId, UCallbackDispatcher* InCallbackDispatcher) override;

	void Disable(const worker::EntityId InEntityId, UCallbackDispatcher* CallbackDispatcher);

	void ApplyInitialState(const UAddComponentOpWrapperBase& Op) override;

	DEPRECATED(12.1, "Please use TriggerAutomaticComponentUpdate.")
	void ReplicateChanges(float DeltaSeconds) override;

	void TriggerAutomaticComponentUpdate(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "MetadataComponent")
	void TriggerManualComponentUpdate();

    UPROPERTY(BlueprintAssignable, Category = "MetadataComponent")
    FSpatialComponentUpdated OnEntityTypeUpdate;



	DEPRECATED(12.1, "This function is deprecated, the component updates are now sent automatically. Use MaxUpdatesPerSecond property to control the update frequency, or set it to 0 and use TriggerManualComponentUpdate for more control.")
    UFUNCTION(BlueprintCallable, Category = "MetadataComponent", meta=(DeprecatedFunction, DeprecationMessage="This function is deprecated, the component updates are now sent automatically. Use MaxUpdatesPerSecond property to control the update frequency, or set it to 0 and use TriggerManualComponentUpdate for more control."))
    void SendComponentUpdate(UMetadataComponentUpdate* update);

    UPROPERTY(BlueprintAssignable, Category = "MetadataComponent")
    FSpatialComponentUpdated OnComponentUpdate;

	DEPRECATED(12.0, "This function is deprecated, access the EntityType property directly.")
    UFUNCTION(BlueprintPure, Category = "MetadataComponent", meta=(DeprecatedFunction, DeprecationMessage="This function is deprecated, access the EntityType property directly."))
    FString GetEntityType();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EntityType;

private:
	void GenerateSnapshot();

	UPROPERTY()
	UMetadataComponentUpdate* ComponentUpdater;


	FMetadataComponentSnapshot* Snapshot;

    void OnComponentUpdateDispatcherCallback(UComponentUpdateOpWrapperBase& Op);

	void OnAuthorityChangeDispatcherCallback(const worker::AuthorityChangeOp& Op) override;

	void ReplicateChangesInternal();
	void SendComponentUpdateInternal(UMetadataComponentUpdate* update);
    void ApplyComponentUpdate(const improbable::Metadata::Update& update);
	void NotifyUpdate(const improbable::Metadata::Update& update);

};
