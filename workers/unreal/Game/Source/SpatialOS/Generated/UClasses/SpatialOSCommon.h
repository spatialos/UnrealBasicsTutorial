// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#pragma once

#include "SpatialOSWorkerTypes.h"
#include "improbable/spawner/spawner.h"
#include "improbable/player/heartbeat.h"
#include "improbable/standard_library.h"

namespace improbable
{
namespace unreal
{
	using Components = worker::Components< improbable::spawner::Spawner,
		improbable::player::HeartbeatReceiver,
		improbable::player::HeartbeatSender,
		improbable::EntityAcl,
		improbable::Metadata,
		improbable::Position,
		improbable::Persistence >;

} // ::unreal
} // ::improbable

