// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "Coordinates.h"

UCoordinates::UCoordinates()
{
	Underlying.Reset(new improbable::Coordinates(0, 0, 0));
}

UCoordinates* UCoordinates::Init(const improbable::Coordinates& underlying)
{
    Underlying.Reset(new improbable::Coordinates(underlying));
	return this;
}

float UCoordinates::GetX()
{
    return static_cast<float>(Underlying->x());
}
UCoordinates* UCoordinates::SetX(float x)
{
    Underlying->set_x(static_cast<double>(x));
	return this;
}

float UCoordinates::GetY()
{
    return static_cast<float>(Underlying->y());
}
UCoordinates* UCoordinates::SetY(float y)
{
    Underlying->set_y(static_cast<double>(y));
	return this;
}

float UCoordinates::GetZ()
{
    return static_cast<float>(Underlying->z());
}
UCoordinates* UCoordinates::SetZ(float z)
{
    Underlying->set_z(static_cast<double>(z));
	return this;
}


improbable::Coordinates UCoordinates::GetUnderlying()
{
	return *Underlying.Get();
}
