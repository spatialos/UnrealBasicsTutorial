// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "SpawnPlayerRequest.h"

USpawnPlayerRequest::USpawnPlayerRequest()
{
	Underlying.Reset(new improbable::spawner::SpawnPlayerRequest(improbable::Coordinates(0, 0, 0)));
}

USpawnPlayerRequest* USpawnPlayerRequest::Init(const improbable::spawner::SpawnPlayerRequest& underlying)
{
    Underlying.Reset(new improbable::spawner::SpawnPlayerRequest(underlying));
	return this;
}

FVector USpawnPlayerRequest::GetPosition()
{
    return USpatialOSConversionFunctionLibrary::SpatialOsCoordinatesToUnrealCoordinates(FVector(static_cast<float>(Underlying->position().x()), static_cast<float>(Underlying->position().y()), static_cast<float>(Underlying->position().z())));
}
USpawnPlayerRequest* USpawnPlayerRequest::SetPosition(FVector position)
{
    Underlying->set_position(USpatialOSConversionFunctionLibrary::UnrealCoordinatesToSpatialOsCoordinatesCast(position));
	return this;
}


improbable::spawner::SpawnPlayerRequest USpawnPlayerRequest::GetUnderlying()
{
	return *Underlying.Get();
}
