#pragma once


//#include "DX.h"
#include <string>
#include <Windows.h>
#include <memory>
#include "DXRenderer.h"

struct ResolutionStruct
{
	UINT uWidth;
	UINT uHeight;
};

#include "DXGraphicsDevice.h"
//#include "DXGeometryInstance.h"

extern HWND hwnd;

class DXGraphicEngine
{
protected:
	// Light
	class CLightEffect* lpLightEffect;

	//Test Geometry
	//DXGeometryInstance* pcGeometryEngine;

public:

	static DXGraphicEngine* getInstance()
	{
		static DXGraphicEngine inst;
		return &inst;
	}

	int iLastPrimitiveCount = 0;
	int iLastPrimitiveType = 0;
	DWORD dwLastVertexType = 0;
	PVOID pLastRenderPtr = NULL;

	ResolutionStruct sResolution;

	virtual ~DXGraphicEngine();

	void Log(char* pszFormat, ...);
	void Error(char* pszFormat, ...);

	// Initialization
	BOOL InitD3D(HWND hWindow, const int screenWidth, const int screenHeight);

	BOOL CreateInterface();
	BOOL CreateDevice(HWND hWnd, int iWidth, int iHeight);
	BOOL CreateVertexBuffer();

	// Getters 
	LPDIRECT3DDEVICE9 GetDevice() { return lpD3DDev; };
	DX::GraphicsDevice_ptr GetGraphicsDevice() { return pGraphicsDevice; };
	int GetWidthBackBuffer() { return d3dPP.BackBufferWidth; };
	int GetHeightBackBuffer() { return d3dPP.BackBufferHeight; };
	HWND GetWindowHandler() { return hwnd; };
	D3DPRESENT_PARAMETERS& Get3DPP() { return d3dPP; }
	LPDIRECT3DVERTEXBUFFER9 GetVertexBuffer(int i) { return lpVertexBuffer[i]; }
	LPDIRECT3DINDEXBUFFER9 GetIndexBuffer(int i) { return lpIndexBuffer[i]; }
	void DrawRectangle2D(class Rectangle2D rRect, DWORD dwColor);
	void DrawRectangle2D(class Rectangle2D sBox, DWORD dwColor1, DWORD dwColor2);

	// Scene
	bool BeginScene();
	bool BeginScene(D3DXMATRIX mView);
	bool EndScene();
	void StateSetup();
	BOOL Reset(const int& screenWidth, const int& screenHeight);
	BOOL SaveRenderTargetToFile(const char* pszFilePath);
	UINT GetVideoMemory();
	std::string GetVideoName();
	UINT GetVertexSize(DWORD dwVertexTypeDesc);
	BOOL DrawPrimitive(D3DPRIMITIVETYPE d3dPrimitiveType, DWORD dwVertexTypeDesc, int iPrimitiveCount, LPVOID pVertices);
	BOOL DrawIndexedPrimitive(D3DPRIMITIVETYPE d3dPrimitiveType, DWORD dwVertexTypeDesc, int iPrimitiveCount, LPVOID pVertices);
	BOOL DrawIndexedPrimitiveGeo(D3DPRIMITIVETYPE d3dPrimitiveType, DWORD dwVertexTypeDesc, int iPrimitiveCount, LPVOID pVertices);
	BOOL DrawLast();
	DWORD GetTextureAverageColor(LPDIRECT3DTEXTURE9 lpTexture, UINT uWidth, UINT uHeight, BOOL bHighColor);
	void OnResetDevice();
	void OnLostDevice();
	void ReloadPostProcess();
	BOOL CheckDevice();

private:
	DXGraphicEngine();
	D3DPRESENT_PARAMETERS d3dPP;
	LPDIRECT3D9 lpD3D;
	LPDIRECT3DDEVICE9 lpD3DDev;
	D3DDISPLAYMODE d3dDM;
	D3DCAPS9 d3dCaps;
	LPDIRECT3DVERTEXBUFFER9 lpVertexBuffer[5];
	LPDIRECT3DINDEXBUFFER9 lpIndexBuffer[5];

	DX::Renderer_ptr pRenderer;
	DX::GraphicsDevice_ptr pGraphicsDevice;

	ID3DXLine* pRectangleUI;
	BOOL bCreatedRectangle;

	HRESULT hr;
	bool antiAliasing;
	bool vSync;
};

#define GRAPHICENGINE (DXGraphicEngine::getInstance())
#define GRAPHICDEVICE GRAPHICENGINE->GetDevice()

