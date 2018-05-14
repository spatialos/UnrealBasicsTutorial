// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "Vector3f.h"

UVector3f::UVector3f()
{
	Underlying.Reset(new improbable::Vector3f(0, 0, 0));
}

UVector3f* UVector3f::Init(const improbable::Vector3f& underlying)
{
    Underlying.Reset(new improbable::Vector3f(underlying));
	return this;
}

float UVector3f::GetX()
{
    return Underlying->x();
}
UVector3f* UVector3f::SetX(float x)
{
    Underlying->set_x(x);
	return this;
}

float UVector3f::GetY()
{
    return Underlying->y();
}
UVector3f* UVector3f::SetY(float y)
{
    Underlying->set_y(y);
	return this;
}

float UVector3f::GetZ()
{
    return Underlying->z();
}
UVector3f* UVector3f::SetZ(float z)
{
    Underlying->set_z(z);
	return this;
}


improbable::Vector3f UVector3f::GetUnderlying()
{
	return *Underlying.Get();
}
