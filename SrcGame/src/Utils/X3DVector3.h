#pragma once

namespace X3D
{

	class Vector3
	{
	public:
		float x, y, z;

		Vector3 operator *(const float f)
		{
			Vector3 v;

			v.x = x * f;
			v.y = y * f;
			v.z = z * f;

			return v;
		};

		Vector3 operator +(const Vector3& c)
		{
			Vector3 v;

			v.x = x + c.x;
			v.y = y + c.y;
			v.z = z + c.z;

			return v;
		};
	};

};

static D3DXVECTOR3 X3DVector3ToD3DXVector3(X3D::Vector3& v)
{
	D3DXVECTOR3 c;
	c.x = v.x;
	c.y = v.y;
	c.z = v.z;

	return c;
}