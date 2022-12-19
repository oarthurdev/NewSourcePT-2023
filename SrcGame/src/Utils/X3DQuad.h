#pragma once

#include "X3DVector3.h"

namespace X3D
{

	class Vector3;

	class Quad
	{
	public:
		Vector3		p1, p2, p3, p4;

		Quad(Vector3 c1, Vector3 c2, Vector3 c3, Vector3 c4) : p1(c1), p2(c2), p3(c3), p4(c4) {};
	};

};