// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "PositionComponentUpdate.h"

improbable::Position::Update UPositionComponentUpdate::DefaultUnderlying = improbable::Position::Update();

UPositionComponentUpdate::UPositionComponentUpdate()
{
}

UPositionComponentUpdate* UPositionComponentUpdate::Init(const improbable::Position::Update& underlying)
{
	return InitInternal(underlying);
}

UPositionComponentUpdate* UPositionComponentUpdate::Reset()
{
	return ResetInternal();
}

bool UPositionComponentUpdate::HasCoords()
{
    return !Underlying.coords().empty();
}

FVector UPositionComponentUpdate::GetCoords()
{
	Coords = USpatialOSConversionFunctionLibrary::SpatialOsCoordinatesToUnrealCoordinates(FVector(static_cast<float>((*(Underlying.coords().data())).x()), static_cast<float>((*(Underlying.coords().data())).y()), static_cast<float>((*(Underlying.coords().data())).z())));
    return Coords;
}

UPositionComponentUpdate* UPositionComponentUpdate::SetCoords(FVector newValue)
{
    return SetCoordsInternal(newValue);
}

const improbable::Position::Update UPositionComponentUpdate::GetUnderlying()
{
    return GetUnderlyingInternal();
}

UPositionComponentUpdate* UPositionComponentUpdate::InitInternal(const improbable::Position::Update& underlying)
{
    Underlying = improbable::Position::Update(underlying);
	return this;
}

UPositionComponentUpdate* UPositionComponentUpdate::ResetInternal()
{
	return InitInternal(DefaultUnderlying);
}

UPositionComponentUpdate* UPositionComponentUpdate::SetCoordsInternal(FVector newValue)
{
    Underlying.set_coords(USpatialOSConversionFunctionLibrary::UnrealCoordinatesToSpatialOsCoordinatesCast(newValue));
	return this;
}

const improbable::Position::Update UPositionComponentUpdate::GetUnderlyingInternal()
{
    return Underlying;
}
