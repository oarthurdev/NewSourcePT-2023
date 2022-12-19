#pragma once

namespace X3D
{

	class Vector4
	{
	public:
		union
		{
			float x, y, z, w;
			float f[4];
		};

		Vector4 operator *(const float fv)
		{
			Vector4 v;

			v.x = x * fv;
			v.y = y * fv;
			v.z = z * fv;
			v.w = w * fv;

			return v;
		};

		Vector4 operator +(const Vector4& c)
		{
			Vector4 v;

			v.x = x + c.x;
			v.y = y + c.y;
			v.z = z + c.z;
			v.w = w + c.w;

			return v;
		};
	};

};

static D3DXVECTOR4 X3DD3DVECTOR4ToD3DXD3DVECTOR4(X3D::Vector4& v)
{
	D3DXVECTOR4 c;
	c.x = v.x;
	c.y = v.y;
	c.z = v.z;
	c.w = v.w;

	return c;
}