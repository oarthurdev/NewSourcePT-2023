#pragma once

#include "X3DVector3.h"

namespace X3D
{

class Vector3;

class Frustum
{
public:
	Vector3		ntl, nbl, ntr, nbr;
	Vector3		ftl, fbl, ftr, fbr;
	Vector3		vPlanes[6];
};

};