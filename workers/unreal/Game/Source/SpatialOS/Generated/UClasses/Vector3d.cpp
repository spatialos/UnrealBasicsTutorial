// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "Vector3d.h"

UVector3d::UVector3d()
{
	Underlying.Reset(new improbable::Vector3d(0, 0, 0));
}

UVector3d* UVector3d::Init(const improbable::Vector3d& underlying)
{
    Underlying.Reset(new improbable::Vector3d(underlying));
	return this;
}

float UVector3d::GetX()
{
    return static_cast<float>(Underlying->x());
}
UVector3d* UVector3d::SetX(float x)
{
    Underlying->set_x(static_cast<double>(x));
	return this;
}

float UVector3d::GetY()
{
    return static_cast<float>(Underlying->y());
}
UVector3d* UVector3d::SetY(float y)
{
    Underlying->set_y(static_cast<double>(y));
	return this;
}

float UVector3d::GetZ()
{
    return static_cast<float>(Underlying->z());
}
UVector3d* UVector3d::SetZ(float z)
{
    Underlying->set_z(static_cast<double>(z));
	return this;
}


improbable::Vector3d UVector3d::GetUnderlying()
{
	return *Underlying.Get();
}
