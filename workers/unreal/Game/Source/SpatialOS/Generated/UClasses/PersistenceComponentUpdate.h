// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ComponentUpdateOpWrapperBase.h"
#include "improbable/standard_library.h"


#include "PersistenceComponentUpdate.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API UPersistenceComponentUpdate : public UComponentUpdateOpWrapperBase
{
    GENERATED_BODY()

  public:
    UPersistenceComponentUpdate();
    
	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
	UPersistenceComponentUpdate* Init(const improbable::Persistence::Update& underlying);
	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
	UPersistenceComponentUpdate* Reset();

	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
    const improbable::Persistence::Update GetUnderlying();

  private:
    friend class UPersistenceComponent;
	friend class UCallbackDispatcher;

	UPersistenceComponentUpdate* InitInternal(const improbable::Persistence::Update& underlying);
	UPersistenceComponentUpdate* ResetInternal();

    const improbable::Persistence::Update GetUnderlyingInternal();


    improbable::Persistence::Update Underlying;
	static improbable::Persistence::Update DefaultUnderlying;
};
