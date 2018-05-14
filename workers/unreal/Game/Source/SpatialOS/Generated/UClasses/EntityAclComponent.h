// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "SpatialOsComponent.h"
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "EntityAclComponentUpdate.h"
#include "EntityAclAddComponentOp.h"
#include "ComponentId.h"
#include "SpatialOSViewTypes.h"
#include "SpatialOSWorkerTypes.h"
#include "improbable/standard_library.h"

#include "WorkerRequirementSet.h"
#include "StdUint32TToImprobableWorkerRequirementSetMap.h"


#include "EntityAclComponent.generated.h"

class UCallbackDispatcher;
class UComponentUpdateOpWrapperBase;

USTRUCT()
struct FEntityAclComponentSnapshot
{
	GENERATED_BODY()

	FEntityAclComponentSnapshot()
	: ReadAcl(improbable::WorkerRequirementSet::Create())
	{
	}

	improbable::WorkerRequirementSet ReadAcl;
	worker::Map<std::uint32_t, improbable::WorkerRequirementSet> ComponentWriteAcl;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPATIALOS_API UEntityAclComponent : public USpatialOsComponent
{
    GENERATED_BODY()

public:
    UEntityAclComponent();
	virtual ~UEntityAclComponent() override = default;

    virtual void BeginDestroy() override;

    UFUNCTION(BlueprintPure, Category = "EntityAclComponent")
    FComponentId GetComponentId();

    const static worker::ComponentId ComponentId;

    void Init(const TWeakPtr<SpatialOSConnection>& InConnection, const TWeakPtr<SpatialOSView>& InView, worker::EntityId InEntityId, UCallbackDispatcher* InCallbackDispatcher) override;

	void Disable(const worker::EntityId InEntityId, UCallbackDispatcher* CallbackDispatcher);

	void ApplyInitialState(const UAddComponentOpWrapperBase& Op) override;

	DEPRECATED(12.1, "Please use TriggerAutomaticComponentUpdate.")
	void ReplicateChanges(float DeltaSeconds) override;

	void TriggerAutomaticComponentUpdate(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "EntityAclComponent")
	void TriggerManualComponentUpdate();

    UPROPERTY(BlueprintAssignable, Category = "EntityAclComponent")
    FSpatialComponentUpdated OnReadAclUpdate;

    UPROPERTY(BlueprintAssignable, Category = "EntityAclComponent")
    FSpatialComponentUpdated OnComponentWriteAclUpdate;



	DEPRECATED(12.1, "This function is deprecated, the component updates are now sent automatically. Use MaxUpdatesPerSecond property to control the update frequency, or set it to 0 and use TriggerManualComponentUpdate for more control.")
    UFUNCTION(BlueprintCallable, Category = "EntityAclComponent", meta=(DeprecatedFunction, DeprecationMessage="This function is deprecated, the component updates are now sent automatically. Use MaxUpdatesPerSecond property to control the update frequency, or set it to 0 and use TriggerManualComponentUpdate for more control."))
    void SendComponentUpdate(UEntityAclComponentUpdate* update);

    UPROPERTY(BlueprintAssignable, Category = "EntityAclComponent")
    FSpatialComponentUpdated OnComponentUpdate;

	DEPRECATED(12.0, "This function is deprecated, access the ReadAcl property directly.")
    UFUNCTION(BlueprintPure, Category = "EntityAclComponent", meta=(DeprecatedFunction, DeprecationMessage="This function is deprecated, access the ReadAcl property directly."))
    UWorkerRequirementSet* GetReadAcl();
	DEPRECATED(12.0, "This function is deprecated, access the ComponentWriteAcl property directly.")
    UFUNCTION(BlueprintPure, Category = "EntityAclComponent", meta=(DeprecatedFunction, DeprecationMessage="This function is deprecated, access the ComponentWriteAcl property directly."))
    UStdUint32TToImprobableWorkerRequirementSetMap* GetComponentWriteAcl();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UWorkerRequirementSet* ReadAcl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStdUint32TToImprobableWorkerRequirementSetMap* ComponentWriteAcl;

private:
	void GenerateSnapshot();

	UPROPERTY()
	UEntityAclComponentUpdate* ComponentUpdater;


	FEntityAclComponentSnapshot* Snapshot;

    void OnComponentUpdateDispatcherCallback(UComponentUpdateOpWrapperBase& Op);

	void OnAuthorityChangeDispatcherCallback(const worker::AuthorityChangeOp& Op) override;

	void ReplicateChangesInternal();
	void SendComponentUpdateInternal(UEntityAclComponentUpdate* update);
    void ApplyComponentUpdate(const improbable::EntityAcl::Update& update);
	void NotifyUpdate(const improbable::EntityAcl::Update& update);

};
