// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AddComponentOpWrapperBase.h"
#include "SpatialOSWorkerTypes.h"
#include "improbable/spawner/spawner.h"
#include "SpawnerAddComponentOp.generated.h"

/**
*
*/
UCLASS()
class SPATIALOS_API USpawnerAddComponentOp : public UAddComponentOpWrapperBase
{
	GENERATED_BODY()

public:
	USpawnerAddComponentOp() {}

    ::worker::Option<improbable::spawner::SpawnerData> Data;
private:
};
