// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ComponentUpdateOpWrapperBase.h"
#include "improbable/standard_library.h"

#include "WorkerRequirementSet.h"
#include "StdUint32TToImprobableWorkerRequirementSetMap.h"

#include "EntityAclComponentUpdate.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UEntityAclComponentUpdate : public UComponentUpdateOpWrapperBase
{
    GENERATED_BODY()

  public:
    UEntityAclComponentUpdate();
    
	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
	UEntityAclComponentUpdate* Init(const improbable::EntityAcl::Update& underlying);
	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
	UEntityAclComponentUpdate* Reset();

	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
    UFUNCTION(BlueprintPure, Category = "EntityAclComponentUpdate")
    bool HasReadAcl();

	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
    UFUNCTION(BlueprintPure, Category = "EntityAclComponentUpdate", meta=(DeprecatedFunction, DeprecationMessage="This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate."))
    UWorkerRequirementSet* GetReadAcl();

	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
    UFUNCTION(BlueprintCallable, Category = "EntityAclComponentUpdate", meta=(DeprecatedFunction, DeprecationMessage="This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate."))
    UEntityAclComponentUpdate* SetReadAcl(UWorkerRequirementSet* newValue);

	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
    UFUNCTION(BlueprintPure, Category = "EntityAclComponentUpdate")
    bool HasComponentWriteAcl();

	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
    UFUNCTION(BlueprintPure, Category = "EntityAclComponentUpdate", meta=(DeprecatedFunction, DeprecationMessage="This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate."))
    UStdUint32TToImprobableWorkerRequirementSetMap* GetComponentWriteAcl();

	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
    UFUNCTION(BlueprintCallable, Category = "EntityAclComponentUpdate", meta=(DeprecatedFunction, DeprecationMessage="This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate."))
    UEntityAclComponentUpdate* SetComponentWriteAcl(UStdUint32TToImprobableWorkerRequirementSetMap* newValue);

	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
    const improbable::EntityAcl::Update GetUnderlying();

  private:
    friend class UEntityAclComponent;
	friend class UCallbackDispatcher;

	UEntityAclComponentUpdate* InitInternal(const improbable::EntityAcl::Update& underlying);
	UEntityAclComponentUpdate* ResetInternal();

    UEntityAclComponentUpdate* SetReadAclInternal(UWorkerRequirementSet* newValue);

    UEntityAclComponentUpdate* SetComponentWriteAclInternal(UStdUint32TToImprobableWorkerRequirementSetMap* newValue);

    const improbable::EntityAcl::Update GetUnderlyingInternal();

	UPROPERTY()
	UWorkerRequirementSet* ReadAcl;
	UPROPERTY()
	UStdUint32TToImprobableWorkerRequirementSetMap* ComponentWriteAcl;

    improbable::EntityAcl::Update Underlying;
	static improbable::EntityAcl::Update DefaultUnderlying;
};
