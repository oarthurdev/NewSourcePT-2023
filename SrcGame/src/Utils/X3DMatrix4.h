#pragma once

namespace X3D
{

	class Matrix4
	{
	public:
		union
		{
			struct
			{
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;

			};
			float m[4][4];
		};


	};

};

static D3DXMATRIX X3DMatrixToD3DXMatrix(const X3D::Matrix4& m)
{
	D3DXMATRIX c;

	CopyMemory(c.m, m.m, sizeof(float) * 4 * 4);

	return c;
}

static X3D::Matrix4 D3DXMatrixToX3DMatrix(const D3DXMATRIX& m)
{
	X3D::Matrix4 c;

	CopyMemory(c.m, m.m, sizeof(float) * 4 * 4);

	return c;
}

