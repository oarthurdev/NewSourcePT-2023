
#include <d3dx9.h>
#include "DXCamera.h"
//#include "DXInit.h"
#include "helper/Geometry.h"

CDXCamera::CDXCamera()
{
}

void CDXCamera::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void CDXCamera::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}


void CDXCamera::GetCoord(D3DXVECTOR3* CamCoords)
{
	if (UNITDATA != 0)
	{
		CamCoords->x = (float) * (int*)(UNITDATA + 0x1E0) + *(int*)GeoCoordX;
		CamCoords->y = (float) * (int*)(UNITDATA + 0x1E4) + *(int*)GeoCoordY;
		CamCoords->z = (float) * (int*)(UNITDATA + 0x1E8) + *(int*)GeoCoordZ;
	}
}


D3DXVECTOR3 CDXCamera::GetPosition()
{
	return D3DXVECTOR3(m_positionX, m_positionY, m_positionZ);
}


D3DXVECTOR3 CDXCamera::GetRotation()
{
	return D3DXVECTOR3(m_rotationX, m_rotationY, m_rotationZ);
}


void CDXCamera::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	// DX::DXInit_ptr pDX = std::make_shared<DX::DXInit>();

	// Setup the vector that points upwards.
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	// Setup the position of the camera in the world.
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;

	// Setup where the camera is looking by default.
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);

	return;
}


void CDXCamera::ConvertCameraTo2D(D3DXVECTOR3* rpos, D3DXVECTOR3 vec)
{
	/*

	 D3DXVECTOR4 pos;
	 D3DXVECTOR3 npos;
	 D3DXMATRIX mView;
	 D3DXMATRIX mProj;
	 D3DXMATRIX mWorld;
	 D3DVIEWPORT9 vPT;

	 DX::DXInit_ptr pDX = std::make_shared<DX::DXInit>();
	 pDX->GetDevice( )->GetTransform( D3DTS_PROJECTION, &mProj );
	 pDX->GetDevice( )->GetTransform( D3DTS_VIEW, &mView );
	 pDX->GetDevice( )->GetTransform( D3DTS_WORLD, &mWorld );
	 pDX->GetDevice()->GetViewport( &vPT );


	 D3DXVec3Transform( &pos, &vec, &mView );
	 npos.x = pos.x;
	 npos.y = pos.y;
	 npos.z = pos.z;
	 D3DXVec3Transform( &pos, &npos, &mProj );
	 pos.x = 800 * ( pos.x + 1.0f ) / 2.0f;
	 pos.y = 600 * ( 1.0f - ( ( pos.y + 1.0f ) / 2.0f ) );
	 pos = pos / pos.w;
	// char MSG[ 512 ] = { 0 };
	// sprintf_s( MSG, "> Test %f - %f [%f, %f, %f]", pos.x, pos.y, vec.x, vec.y, vec.z );
	// CHATMESSAGE( MSG, 0 );
	 */
}


void CDXCamera::GetViewMatrix(D3DXMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}

CDXCamera::~CDXCamera()
{
}
