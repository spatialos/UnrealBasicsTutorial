// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "improbable/standard_library.h"

#include "WorkerRequirementSet.h"
#include "StdUint32TToImprobableWorkerRequirementSetMap.h"
#include "EntityAclData.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UEntityAclData : public UObject
{
    GENERATED_BODY()

  public:
    UEntityAclData();
    UEntityAclData* Init(const improbable::EntityAclData& underlying);

    UFUNCTION(BlueprintPure, Category = "EntityAclData")
    UWorkerRequirementSet* GetReadAcl();
	UFUNCTION(BlueprintCallable, Category = "EntityAclData")
    UEntityAclData* SetReadAcl(UWorkerRequirementSet* read_acl);

    UFUNCTION(BlueprintPure, Category = "EntityAclData")
    UStdUint32TToImprobableWorkerRequirementSetMap* GetComponentWriteAcl();
	UFUNCTION(BlueprintCallable, Category = "EntityAclData")
    UEntityAclData* SetComponentWriteAcl(UStdUint32TToImprobableWorkerRequirementSetMap* component_write_acl);


	improbable::EntityAclData GetUnderlying();

  private:
    TUniquePtr<improbable::EntityAclData> Underlying;
};

