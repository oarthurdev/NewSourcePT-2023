#pragma once


class CDXCamera
{
private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXVECTOR3 CamCoords{ 0, 0, 0 };
	D3DXMATRIX m_viewMatrix;
public:
	const int GeoCoordX = 0x35BF3F8;
	const int GeoCoordY = GeoCoordX + 4;
	const int GeoCoordZ = GeoCoordY + 4;

	CDXCamera();
	void SetPosition(float, float, float);
	void SetRotation(float, float, float);
	void GetCoord(D3DXVECTOR3* CamCoords);
	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	void ConvertCameraTo2D(D3DXVECTOR3* pos, D3DXVECTOR3 vec);
	void Render();
	void GetViewMatrix(D3DXMATRIX&);
	~CDXCamera();
};

