// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ComponentUpdateOpWrapperBase.h"
#include "improbable/spawner/spawner.h"


#include "SpawnerComponentUpdate.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class SPATIALOS_API USpawnerComponentUpdate : public UComponentUpdateOpWrapperBase
{
    GENERATED_BODY()

  public:
    USpawnerComponentUpdate();
    
	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
	USpawnerComponentUpdate* Init(const improbable::spawner::Spawner::Update& underlying);
	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
	USpawnerComponentUpdate* Reset();

	DEPRECATED(12.1, "This class is deprecated, please access the Component properties directly and use automatic component updates or explicitly trigger a manual update with TriggerManualComponentUpdate.")
    const improbable::spawner::Spawner::Update GetUnderlying();

  private:
    friend class USpawnerComponent;
	friend class UCallbackDispatcher;

	USpawnerComponentUpdate* InitInternal(const improbable::spawner::Spawner::Update& underlying);
	USpawnerComponentUpdate* ResetInternal();

    const improbable::spawner::Spawner::Update GetUnderlyingInternal();


    improbable::spawner::Spawner::Update Underlying;
	static improbable::spawner::Spawner::Update DefaultUnderlying;
};
