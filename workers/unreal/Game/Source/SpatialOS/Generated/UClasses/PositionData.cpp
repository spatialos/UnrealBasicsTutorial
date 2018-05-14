// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "PositionData.h"

UPositionData::UPositionData()
{
	Underlying.Reset(new improbable::PositionData(improbable::Coordinates(0, 0, 0)));
}

UPositionData* UPositionData::Init(const improbable::PositionData& underlying)
{
    Underlying.Reset(new improbable::PositionData(underlying));
	return this;
}

FVector UPositionData::GetCoords()
{
    return USpatialOSConversionFunctionLibrary::SpatialOsCoordinatesToUnrealCoordinates(FVector(static_cast<float>(Underlying->coords().x()), static_cast<float>(Underlying->coords().y()), static_cast<float>(Underlying->coords().z())));
}
UPositionData* UPositionData::SetCoords(FVector coords)
{
    Underlying->set_coords(USpatialOSConversionFunctionLibrary::UnrealCoordinatesToSpatialOsCoordinatesCast(coords));
	return this;
}


improbable::PositionData UPositionData::GetUnderlying()
{
	return *Underlying.Get();
}
