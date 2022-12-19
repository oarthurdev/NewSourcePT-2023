#include <memory>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "DXGraphicEngine.h"
#include "DX.h"
#include "DXSelectGlow.h"
#include "UIImage.h"
#include "UIImageRender.h"
#include "smLib3d/smDsx.h"
#include "Utils/Macros.h"
#include "Utils/String.h"
#include "Utils/_common.h"
#include "Utils/Geometry.h"
#include "Utils/EXEVertex.h"
#include "Utils/debug.h"
#include "Utils/Macros.h"
#include "def.h"
#include "Settings/Settings.h"


#pragma comment(lib, "d3d9.lib") 
#pragma comment(lib, "d3dx9.lib")

DXGraphicEngine::DXGraphicEngine()
{
	ZeroMemory(&d3dDM, sizeof(D3DDISPLAYMODE));
	ZeroMemory(&d3dCaps, sizeof(D3DCAPS9));
	ZeroMemory(&d3dPP, sizeof(D3DPRESENT_PARAMETERS));

	lpD3D = NULL;
	lpD3DDev = NULL;
	lpLightEffect = NULL;

	antiAliasing = false;
	vSync = false;
}

DXGraphicEngine::~DXGraphicEngine()
{
}

void DXGraphicEngine::Log(char* pszFormat, ...)
{
	va_list vl;

	DX::Logger Log;

	char szError[16384];

	va_start(vl, pszFormat);
	_vsnprintf_s(szError, _countof(szError), _TRUNCATE, pszFormat, vl);
	va_end(vl);

	char szMessage[4096];
	STRINGFORMAT(szMessage, "[%08X][%s] %s\r\n", hr, Log.ResultToString(hr), szError);

	FILE* file;
	CreateDirectoryA("save\\logs", NULL);
	if (fopen_s(&file, "save\\logs\\init.log", "a") == 0)
	{
		fputs(szMessage, file);
		fflush(file);
		fclose(file);
	}
}

void DXGraphicEngine::Error(char* pszFormat, ...)
{
	va_list vl;

	DX::Logger DXLog;

	char szError[16384];

	va_start(vl, pszFormat);
	_vsnprintf_s(szError, _countof(szError), _TRUNCATE, pszFormat, vl);
	va_end(vl);

	char szMessage[4096];
	STRINGFORMAT(szMessage, "[%08X][%s] %s", hr, DXLog.ResultToString(hr), szError);

	MessageBoxA(0, szMessage, "Graphic Engine Error!", MB_OK | MB_ICONEXCLAMATION);

	Log(szError);
}

BOOL DXGraphicEngine::InitD3D(HWND hWindow, const int screenWidth, const int screenHeight)
{
	// Create the Direct3D interface
	CreateInterface();

	// Create a device class
	CreateDevice(hWindow, screenWidth, screenHeight);

	// Rectangle UI
	if (!bCreatedRectangle)
	{
		D3DXCreateLine(GRAPHICENGINE->GetDevice(), &pRectangleUI);
		bCreatedRectangle = TRUE;
	}

	pGraphicsDevice = std::make_shared<DX::GraphicsDevice>(lpD3DDev);
	pRenderer = std::make_shared<DX::Renderer>(pGraphicsDevice);

	////Video Renderer
	//pcVideoRenderer = new DXVideoRenderer();

	DX::cSelectGlow1.Init(pRenderer);
	DX::cSelectGlow2.Init(pRenderer);

	//// Set display mode
	//CALL_WITH_ARG3(0x0063B220, READDWORD(0x00824F70), READDWORD(0x00824F74), READDWORD(0x00824F78));

	//CALL(0x0041BD10);

	return TRUE;
}

BOOL DXGraphicEngine::CreateInterface()
{
	bool bAntiAliasing = false;

	DX::Logger DXLog;

	if (FAILED(lpD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		DXLog.Print("Could not Create Direct3D");
		MessageBox(0, "Could not Create Direct3D", "Engine Graphic", 0);
		return FALSE;
	}

	if (FAILED(hr = lpD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dDM)))
	{
		// Error
		return FALSE;
	}

	// Window mode
	BOOL bWindowed = TRUE;

	// Bit Depth is 32 or 16
	DWORD dwBitDepth = 32;

	// Support 32 or 16 bits BitDepth?
	if (FAILED(hr = lpD3D->CheckDeviceType(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		d3dDM.Format,
		dwBitDepth == 32 ? D3DFMT_X8R8G8B8 : D3DFMT_X4R4G4B4,
		bWindowed)))
	{
		dwBitDepth = dwBitDepth == 32 ? 16 : 32;

		if (FAILED(hr = lpD3D->CheckDeviceType(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			d3dDM.Format,
			dwBitDepth == 32 ? D3DFMT_X8R8G8B8 : D3DFMT_X4R4G4B4,
			bWindowed)))
		{
			Error("Your device must support a 16 or 32 bit Back Buffer");
			DXLog.Print("DEVICE BITDEPTH CANNOT SUPPORT 32 OR 16 BIT");
			return FALSE;
		}
	}

	if (dwBitDepth == 32)
	{
		Log("32 bit Back Buffer");
		d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else if (dwBitDepth == 16)
	{
		Log("16 bit Back Buffer");
		d3dPP.BackBufferFormat = D3DFMT_X4R4G4B4;
	}
	else
	{
		Log("Unknown Back Buffer Format");
		return FALSE;
	}

	d3dPP.AutoDepthStencilFormat = D3DFMT_D24S8;

	if (FAILED(hr = lpD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		d3dDM.Format,
		D3DUSAGE_DEPTHSTENCIL,
		D3DRTYPE_SURFACE,
		d3dPP.AutoDepthStencilFormat)))
	{
		d3dPP.AutoDepthStencilFormat = D3DFMT_D15S1;

		if (FAILED(hr = lpD3D->CheckDeviceFormat(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			d3dDM.Format,
			D3DUSAGE_DEPTHSTENCIL,
			D3DRTYPE_SURFACE,
			d3dPP.AutoDepthStencilFormat)))
		{
			Error("Your device must support a 16(1s) or 32(8s) bit DepthStencil Buffer");
			return FALSE;
		}
		else
		{
			Log("D15S1 DepthStencil Buffer");
		}
	}
	else
	{
		Log("D24S8 DepthStencil Buffer");
	}

	// MultiSample
	d3dPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dPP.MultiSampleQuality = 0;

	if (bAntiAliasing)
	{
		D3DMULTISAMPLE_TYPE d3daMultipleSampleType[] = {
		D3DMULTISAMPLE_16_SAMPLES,
		D3DMULTISAMPLE_15_SAMPLES,
		D3DMULTISAMPLE_14_SAMPLES,
		D3DMULTISAMPLE_13_SAMPLES,
		D3DMULTISAMPLE_12_SAMPLES,
		D3DMULTISAMPLE_11_SAMPLES,
		D3DMULTISAMPLE_10_SAMPLES,
		D3DMULTISAMPLE_9_SAMPLES,
		D3DMULTISAMPLE_8_SAMPLES,
		D3DMULTISAMPLE_7_SAMPLES,
		D3DMULTISAMPLE_6_SAMPLES,
		D3DMULTISAMPLE_5_SAMPLES,
		D3DMULTISAMPLE_4_SAMPLES,
		D3DMULTISAMPLE_3_SAMPLES,
		D3DMULTISAMPLE_2_SAMPLES,
		};

		for (int i = 0; i < _countof(d3daMultipleSampleType); i++)
		{
			D3DMULTISAMPLE_TYPE t = d3daMultipleSampleType[i];
			DWORD q;

			if (SUCCEEDED(hr = lpD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				d3dPP.BackBufferFormat,
				bWindowed,
				t,
				&q)) &&
				SUCCEEDED(hr = lpD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
					D3DDEVTYPE_HAL,
					d3dPP.AutoDepthStencilFormat,
					bWindowed,
					t,
					&q)))
			{
				d3dPP.MultiSampleType = t;
				d3dPP.MultiSampleQuality = q - 1;
				break;
			}
		}
	}

	//Get Device Caps
	if (FAILED(hr = lpD3D->GetDeviceCaps(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		&d3dCaps)))
	{
		Error("Could not get Device Capabilities");
		return FALSE;
	}
	return TRUE;
}

BOOL DXGraphicEngine::CreateDevice(HWND hWnd, int iWidth, int iHeight)
{
	d3dPP.BackBufferWidth = iWidth;
	d3dPP.BackBufferHeight = iHeight;
	d3dPP.Windowed = TRUE;

	sResolution.uWidth = d3dPP.BackBufferWidth;
	sResolution.uHeight = d3dPP.BackBufferHeight;

	DWORD dwBehaviourFlags = D3DCREATE_FPU_PRESERVE;

	d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if (d3dCaps.DevCaps & D3DDEVCAPS_PUREDEVICE)
	{
		Log("Pure Device");
		dwBehaviourFlags |= D3DCREATE_PUREDEVICE;
	}

	if ((d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) && (d3dCaps.VertexProcessingCaps != 0))
	{
		Log("Hardware Vertex Processing");
		dwBehaviourFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		Log("Software Vertex Processing");
		dwBehaviourFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	if (d3dCaps.PresentationIntervals & D3DPRESENT_INTERVAL_IMMEDIATE)
	{
		Log("Presentation Interval Immediate");
		d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}

	if (vSync)
	{
		if (d3dCaps.PresentationIntervals & D3DPRESENT_INTERVAL_ONE)
		{
			Log("Presentation Interval One");
			d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		}
	}

	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.hDeviceWindow = hWnd;
	d3dPP.BackBufferCount = 1;
	d3dPP.EnableAutoDepthStencil = TRUE;
	d3dPP.Flags = 0;

	if (d3dPP.Windowed)
	{
		d3dPP.FullScreen_RefreshRateInHz = 0;

		if (FAILED(hr = lpD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			dwBehaviourFlags,
			&d3dPP,
			&lpD3DDev)))
		{
			Error("Could not create Direct3D Device");
			return FALSE;
		}

		return TRUE;
	}
	else
	{
		d3dPP.Windowed = FALSE;
		d3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

		if (FAILED(hr = lpD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			dwBehaviourFlags,
			&d3dPP,
			&lpD3DDev)))
		{
			Error("Could not create Direct3D Device");
			return FALSE;
		}
		return TRUE;
	}

}

BOOL DXGraphicEngine::CreateVertexBuffer()
{
	DWORD dwVertexTypeDesc = 324;
	UINT uVertexSize = 28;

	return TRUE;
}

bool DXGraphicEngine::BeginScene()
{
	if (CheckDevice())
	{
		// Clear old render and start render
		if (FAILED(GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0)))
		{
			return false;
		}

		GetDevice()->BeginScene();
		return true;
	}

	return false;
}

bool DXGraphicEngine::BeginScene(D3DXMATRIX mView)
{

	// Clear old render and start render
	if (FAILED(GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0)))
	{
		return false;
	}

	GetDevice()->SetTransform(D3DTS_VIEW, &mView);

	GetDevice()->BeginScene();

	return true;
	// GRAPHICENGINE->StateSetup();

	//Controller::OnBeginScene();
	//GameCore::GetInstance()->Render3D();
}

bool DXGraphicEngine::EndScene()
{
	// Stop render
	GetDevice()->EndScene();
	GetDevice()->Present(NULL, NULL, NULL, NULL);

	return true;
}

void DXGraphicEngine::StateSetup()
{

	//Render States
	lpD3DDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	lpD3DDev->SetRenderState(D3DRS_CLIPPING, TRUE);
	lpD3DDev->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_ARGB(0, 0, 0, 0));

	lpD3DDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	lpD3DDev->SetRenderState(D3DRS_LASTPIXEL, FALSE);

	lpD3DDev->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	lpD3DDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	lpD3DDev->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	lpD3DDev->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	lpD3DDev->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	lpD3DDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	lpD3DDev->SetRenderState(D3DRS_ALPHAREF, 60);
	lpD3DDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	lpD3DDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	lpD3DDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	lpD3DDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	lpD3DDev->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, FALSE);

	for (int i = 0; i < 8; i++)
	{
		lpD3DDev->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		lpD3DDev->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		lpD3DDev->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

		lpD3DDev->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		lpD3DDev->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

		lpD3DDev->SetTexture(i, NULL);
	}
}


void DXGraphicEngine::DrawRectangle2D(Rectangle2D rRect, DWORD dwColor)
{
	D3DXVECTOR2 vLine[2];

	pRectangleUI->SetWidth((float)rRect.iWidth);
	pRectangleUI->SetAntialias(FALSE);
	pRectangleUI->SetGLLines(true);

	vLine[0].x = (float)rRect.iX + (float)rRect.iWidth / 2;
	vLine[0].y = (float)rRect.iY;
	vLine[1].x = (float)rRect.iX + (float)rRect.iWidth / 2;
	vLine[1].y = (float)rRect.iY + (float)rRect.iHeight;

	pRectangleUI->Begin();
	pRectangleUI->Draw(vLine, 2, dwColor);
	pRectangleUI->End();
}

void DXGraphicEngine::DrawRectangle2D(Rectangle2D sBox, DWORD dwColor1, DWORD dwColor2)
{
	float u, v, u2, v2;

	//Compute texture coordinates, it's easy
	u = 0.0f;
	v = 0.0f;
	u2 = 1.0f;
	v2 = 1.0f;

	EXEDrawVertex rVertex[4];
	rVertex[0] = { float(sBox.iX), float(sBox.iY), 0, 1, dwColor1, 0, u, v };
	rVertex[1] = { float(sBox.iX + sBox.iWidth), float(sBox.iY), 0, 1, dwColor1, 0, u2, v };
	rVertex[2] = { float(sBox.iX), float(sBox.iY + sBox.iHeight), 0, 1, dwColor2, 0, u, v2 };
	rVertex[3] = { float(sBox.iX + sBox.iWidth), float(sBox.iY + sBox.iHeight), 0, 1, dwColor2, 0, u2, v2 };

	GRAPHICDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	GRAPHICDEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);
	GRAPHICDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	GRAPHICDEVICE->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	GRAPHICDEVICE->SetRenderState(D3DRS_COLORWRITEENABLE, D3DCOLORWRITEENABLE_RED | D3DCOLORWRITEENABLE_GREEN | D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA);



	GRAPHICDEVICE->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	GRAPHICDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
	GRAPHICDEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GRAPHICDEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GRAPHICDEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	GRAPHICDEVICE->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	//Texture Stage States
	GRAPHICDEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	GRAPHICDEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	GRAPHICDEVICE->SetTexture(0, 0);

	GRAPHICDEVICE->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR);
	GRAPHICDEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, (LPVOID)rVertex, sizeof(EXEDrawVertex));
}

BOOL DXGraphicEngine::DrawPrimitive(D3DPRIMITIVETYPE d3dPrimitiveType, DWORD dwVertexTypeDesc, int iPrimitiveCount, LPVOID pVertices)
{
	if (iPrimitiveCount == 0)
		return TRUE;

	UINT uVertexSize = GetVertexSize(dwVertexTypeDesc);

	iLastPrimitiveCount = iPrimitiveCount;
	iLastPrimitiveType = d3dPrimitiveType;
	dwLastVertexType = dwVertexTypeDesc;
	pLastRenderPtr = pVertices;


	//Set FVF
	if (FAILED(lpD3DDev->SetFVF(dwVertexTypeDesc)))
	{
		WRITEDBG("ERROR - DXGraphicEngine::DrawPrimitive (SetFVF)");
		return FALSE;
	}

	if (FAILED(lpD3DDev->DrawPrimitiveUP(d3dPrimitiveType, iPrimitiveCount, pVertices, uVertexSize)))
	{
		WRITEDBG("ERROR - DXGraphicEngine::DrawPrimitive (DrawPrimitiveUP)");
		return FALSE;
	}

	return TRUE;
}

BOOL DXGraphicEngine::DrawIndexedPrimitive(D3DPRIMITIVETYPE d3dPrimitiveType, DWORD dwVertexTypeDesc, int iPrimitiveCount, LPVOID pVertices)
{
	if (iPrimitiveCount == 0)
		return TRUE;

	UINT uVertexSize = 0;

	LPDIRECT3DINDEXBUFFER9 lpIB = NULL;
	LPDIRECT3DVERTEXBUFFER9 lpVB = NULL;

	//Get Vertex Size
	if (dwVertexTypeDesc == 324)
	{
		uVertexSize = 28;
		lpIB = GetIndexBuffer(0);
		lpVB = GetVertexBuffer(0);
	}
	else if (dwVertexTypeDesc == 452)
	{
		uVertexSize = sizeof(EXEDrawVertex);
		lpIB = GetIndexBuffer(1);
		lpVB = GetVertexBuffer(1);
	}
	else if (dwVertexTypeDesc == 708)
	{
		uVertexSize = sizeof(EXEDrawVertex) + 8;
		lpIB = GetIndexBuffer(2);
		lpVB = GetVertexBuffer(2);
	}
	else if (dwVertexTypeDesc == 964)
	{
		uVertexSize = sizeof(EXEDrawVertex) + 16;
		lpIB = GetIndexBuffer(3);
		lpVB = GetVertexBuffer(3);
	}
	else if (dwVertexTypeDesc == 1220)
	{
		uVertexSize = sizeof(EXEDrawVertex) + 24;
		lpIB = GetIndexBuffer(4);
		lpVB = GetVertexBuffer(4);
	}
	void* pVoid;

	CONST DWORD dwLockFlags = D3DLOCK_DISCARD;

	lpVB->Lock(0, 0, &pVoid, dwLockFlags);
	CopyMemory(pVoid, pVertices, uVertexSize * (iPrimitiveCount * 3));
	lpVB->Unlock();

	lpIB->Lock(0, 0, &pVoid, dwLockFlags);
	//CopyMemory(pVoid, EXERender::saIndices, sizeof(WORD) * EXERender::iIndexIndices);
	lpIB->Unlock();

	lpD3DDev->SetIndices(lpIB);

	//Set FVF
	if (FAILED(lpD3DDev->SetFVF(dwVertexTypeDesc)))
	{
		WRITEDBG("ERROR - DXGraphicEngine::DrawPrimitive (SetFVF)");
		return FALSE;
	}

	lpD3DDev->SetStreamSource(0, lpVB, 0, uVertexSize);

	lpD3DDev->DrawIndexedPrimitive(d3dPrimitiveType, 0, 0, (iPrimitiveCount * 3), 0, iPrimitiveCount);

	return TRUE;
}

BOOL DXGraphicEngine::DrawIndexedPrimitiveGeo(D3DPRIMITIVETYPE d3dPrimitiveType, DWORD dwVertexTypeDesc, int iPrimitiveCount, LPVOID pVertices)
{
	if (dwVertexTypeDesc == 452)
	{
		//pcGeometryEngine->HandleVertices(pVertices, iPrimitiveCount, sizeof(EXEDrawVertex));
		//pcGeometryEngine->HandleIndices(EXERender::saIndices, EXERender::iIndexIndices);
		//pcGeometryEngine->Render(d3dPrimitiveType);
	}
	else
	{
		DrawPrimitive(d3dPrimitiveType, dwVertexTypeDesc, iPrimitiveCount, pVertices);
	}
	return TRUE;
}

BOOL DXGraphicEngine::DrawLast()
{
	return DrawPrimitive((D3DPRIMITIVETYPE)iLastPrimitiveType, dwLastVertexType, iLastPrimitiveCount, pLastRenderPtr);
}

DWORD DXGraphicEngine::GetTextureAverageColor(LPDIRECT3DTEXTURE9 lpTexture, UINT uWidth, UINT uHeight, BOOL bHighColor)
{
	static LPDIRECT3DTEXTURE9 lpLastTexture = NULL;
	static DWORD dwLastColor = 0;

	if (uWidth == 0 || uHeight == 0)
		return 0;

	if (lpTexture == NULL)
		return 0;

	if (lpLastTexture == lpTexture)
		return dwLastColor;

	D3DLOCKED_RECT d3dRect;
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = uWidth;
	rc.bottom = uHeight;

	if (SUCCEEDED(lpTexture->LockRect(0, &d3dRect, &rc, D3DLOCK_READONLY)))
	{
		BYTE* pDest = (BYTE*)d3dRect.pBits;

		UINT uColorsCount = 0;
		UINT uRed = 0;
		UINT uGreen = 0;
		UINT uBlue = 0;

		DX::Color cOldColor(0);

		DX::Color cColor(0);

		struct ColorDominant
		{
			D3DCOLOR d3dColor;
			UINT uRefCount;
		};

		std::vector<ColorDominant*> vColors;

		auto IsNearColor = [](D3DCOLOR color1, D3DCOLOR color2, int iAverage, IMinMax& sMinMax) -> BOOL
		{
			DX::Color cColor1(color1);
			DX::Color cColor2(color2);

			if ((abs(cColor1.GetRed() - cColor2.GetRed()) <= iAverage))
			{
				if (abs(cColor1.GetGreen() - cColor2.GetGreen()) <= iAverage)
				{
					if (abs(cColor1.GetBlue() - cColor2.GetBlue()) <= iAverage)
					{
						if ((cColor1.GetRed() >= sMinMax.iMin) && (cColor1.GetRed() <= sMinMax.iMax))
							if ((cColor1.GetGreen() >= sMinMax.iMin) && (cColor1.GetGreen() <= sMinMax.iMax))
								if ((cColor1.GetBlue() >= sMinMax.iMin) && (cColor1.GetBlue() <= sMinMax.iMax))
									return TRUE;
					}
				}
			}
			return FALSE;
		};

		for (UINT y = 0; y < uHeight; y++)
		{
			for (UINT x = 0; x < uWidth; x++)
			{
				int iIndex = (d3dRect.Pitch * y) + (4 * x);
				cColor.SetRed((int)pDest[iIndex + 2]);
				cColor.SetGreen((int)pDest[iIndex + 1]);
				cColor.SetBlue((int)pDest[iIndex]);

				if (cColor.Get() > 0)
				{
					if (bHighColor)
					{
						BOOL bFound = FALSE;
						for (std::vector<ColorDominant*>::iterator it = vColors.begin(); it != vColors.end(); it++)
						{
							ColorDominant* ps = (*it);

							if ((cColor.Get() == ps->d3dColor) || IsNearColor(cColor.Get(), ps->d3dColor, 15, IMinMax(20, 245)))
							{
								ps->uRefCount++;
								bFound = TRUE;
								break;
							}
						}

						if (bFound == FALSE)
						{
							ColorDominant* ps = new ColorDominant;
							ps->d3dColor = cColor.Get();
							ps->uRefCount = 1;
							vColors.push_back(ps);
						}
					}
					else
					{
						uRed += cColor.GetRed();
						uGreen += cColor.GetGreen();
						uBlue += cColor.GetBlue();
						uColorsCount++;
					}
				}
			}
		}

		lpTexture->UnlockRect(0);

		if (bHighColor)
		{
			UINT uLastRefCount = 0;
			for (std::vector<ColorDominant*>::iterator it = vColors.begin(); it != vColors.end(); it++)
			{
				ColorDominant* ps = (*it);

				if (ps)
				{
					if (ps->uRefCount > uLastRefCount)
					{
						cColor.Set(ps->d3dColor);
						uRed = cColor.GetRed();
						uGreen = cColor.GetGreen();
						uBlue = cColor.GetBlue();
						uLastRefCount = ps->uRefCount;
					}

					DELET(ps);
				}
			}

			if (uLastRefCount > 0)
				uColorsCount = 1;

			vColors.clear();
		}


		cColor.Set(0);
		if (uColorsCount > 0)
		{
			cColor.SetRed(uRed / uColorsCount);
			cColor.SetGreen(uGreen / uColorsCount);
			cColor.SetBlue(uBlue / uColorsCount);
			cColor.SetAlpha(255);
		}

		lpLastTexture = lpTexture;
		dwLastColor = cColor.Get();

		return cColor.Get();
	}

	return 0;
}


void DXGraphicEngine::OnResetDevice()
{
	FONTHANDLER->OnResetDevice();

	// Sprite 2D
	UI::ImageRender::OnResetDevice();

	// Rectangle 2D
	pRectangleUI->OnResetDevice();

	pGraphicsDevice->OnResetDevice();


	//Hide Cursor
	// ShowCursor( FALSE );
}

void DXGraphicEngine::OnLostDevice()
{
	FONTHANDLER->OnLostDevice();

	// Sprite 2D
	UI::ImageRender::OnLostDevice();

	// Rectangle 2D
	pRectangleUI->OnLostDevice();

	pGraphicsDevice->OnLostDevice();

	//Hide Cursor
	//ShowCursor( FALSE );
}

void DXGraphicEngine::ReloadPostProcess()
{
}

BOOL DXGraphicEngine::CheckDevice()
{
	switch (hr = lpD3DDev->TestCooperativeLevel())
	{
	case D3DERR_DEVICELOST:
		OnLostDevice();

		//Yield CPU
		Sleep(500);

		//Log
		Log("CheckDevice(): Device Lost[0x%08X]", hr);

		return FALSE;

	case D3DERR_DEVICENOTRESET:

		OnLostDevice();

		if (FAILED(hr = lpD3DDev->Reset(&d3dPP)))
		{
			//Yield CPU
			Sleep(250);

			//Log
			Log("CheckDevice(): Device Reset Failed [0x%08X]", hr);

			return FALSE;
		}

		InitRender();

		OnResetDevice();

		break;
	}

	return (hr == S_OK);
}

BOOL DXGraphicEngine::Reset(const int& screenWidth, const int& screenHeight)
{
	if (!lpD3D || !lpD3DDev)
		return FALSE;

	if (screenWidth == d3dPP.BackBufferWidth &&
		screenHeight == d3dPP.BackBufferHeight)
	{
		Log("DXGraphicEngine::Reset(%d, %d) aborted", screenWidth, screenHeight);
		return FALSE;
	}

	//Save current PP
	D3DPRESENT_PARAMETERS d3dOldPP;
	CopyMemory(&d3dOldPP, &d3dPP, sizeof(D3DPRESENT_PARAMETERS));

	//Back Buffer
	if (FAILED(hr = lpD3D->CheckDeviceType(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		d3dDM.Format,
		d3dPP.BackBufferFormat,
		SETTINGSHANDLER->getWindowMode())))
	{
		Error("Reset(): CheckDeviceType() failed");

		if (FAILED(hr = lpD3D->CheckDeviceType(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			d3dDM.Format,
			d3dPP.BackBufferFormat == D3DFMT_X8R8G8B8 ? D3DFMT_X4R4G4B4 : D3DFMT_X8R8G8B8,
			SETTINGSHANDLER->getWindowMode())))
			return FALSE;

		d3dPP.BackBufferFormat = (d3dPP.BackBufferFormat == D3DFMT_X8R8G8B8 ? D3DFMT_X4R4G4B4 : D3DFMT_X8R8G8B8);
	}

	if (d3dPP.BackBufferFormat == D3DFMT_X8R8G8B8)
	{
		//32 bit Back Buffer
		Log("DXGraphicEngine::Reset(): 32 bit Back Buffer");
	}
	else if (d3dPP.BackBufferFormat == D3DFMT_X4R4G4B4)
	{
		//16 bit Back Buffer
		Log("DXGraphicEngine::Reset(): 16 bit Back Buffer");
	}
	else
	{
		Error("DXGraphicEngine::Reset(): Unknown Back Buffer Format");
		return FALSE;
	}

	//New Back Buffer Size
	d3dPP.BackBufferWidth = screenWidth;
	d3dPP.BackBufferHeight = screenHeight;

	//Multi Sample
	d3dPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dPP.MultiSampleQuality = 0;

	if (antiAliasing)
	{
		D3DMULTISAMPLE_TYPE d3daMultipleSampleType[] = {
			D3DMULTISAMPLE_16_SAMPLES,
			D3DMULTISAMPLE_15_SAMPLES,
			D3DMULTISAMPLE_14_SAMPLES,
			D3DMULTISAMPLE_13_SAMPLES,
			D3DMULTISAMPLE_12_SAMPLES,
			D3DMULTISAMPLE_11_SAMPLES,
			D3DMULTISAMPLE_10_SAMPLES,
			D3DMULTISAMPLE_9_SAMPLES,
			D3DMULTISAMPLE_8_SAMPLES,
			D3DMULTISAMPLE_7_SAMPLES,
			D3DMULTISAMPLE_6_SAMPLES,
			D3DMULTISAMPLE_5_SAMPLES,
			D3DMULTISAMPLE_4_SAMPLES,
			D3DMULTISAMPLE_3_SAMPLES,
			D3DMULTISAMPLE_2_SAMPLES,
		};

		for (int i = 0; i < _countof(d3daMultipleSampleType); i++)
		{
			D3DMULTISAMPLE_TYPE t = d3daMultipleSampleType[i];
			DWORD q;

			if (SUCCEEDED(hr = lpD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				d3dPP.BackBufferFormat,
				SETTINGSHANDLER->getWindowMode(),
				t,
				&q)) &&
				SUCCEEDED(hr = lpD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT,
					D3DDEVTYPE_HAL,
					d3dPP.AutoDepthStencilFormat,
					SETTINGSHANDLER->getWindowMode(),
					t,
					&q)))
			{
				d3dPP.MultiSampleType = t;
				d3dPP.MultiSampleQuality = q - 1;
				break;
			}
		}
	}

	Log("DXGraphicEngine::Reset(): Multi Sample: %d %d", d3dPP.MultiSampleType, d3dPP.MultiSampleQuality);

	//Window specific PP settings
	if (SETTINGSHANDLER->getWindowMode())
	{
		d3dPP.Windowed = TRUE;
		d3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	}
	else
	{
		d3dPP.Windowed = FALSE;
		d3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	}

	d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if (d3dCaps.PresentationIntervals & D3DPRESENT_INTERVAL_IMMEDIATE)
	{
		Log("DXGraphicEngine::Reset() Presentation Interval Immediate");
		d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}

	if (vSync)
	{
		if (d3dCaps.PresentationIntervals & D3DPRESENT_INTERVAL_ONE)
		{
			Log("DXGraphicEngine::Reset() Presentation Interval One");
			d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		}
	}

	//Lose Device and attempt Reset on new PP
	OnLostDevice();

	if (FAILED(hr = lpD3DDev->Reset(&d3dPP)))
	{
		CopyMemory(&d3dPP, &d3dOldPP, sizeof(D3DPRESENT_PARAMETERS));

		//Log
		Error("DXGraphicEngine::Resize() Device Reset Failed");

		//Yield CPU
		Sleep(400);

		//Reset back to previous (working) PP
		OnLostDevice();

		if (FAILED(hr = lpD3DDev->Reset(&d3dPP)))
		{
			//Log
			Error("DXGraphicEngine::Resize() Device Rollback Failed");

			//Yield CPU
			Sleep(400);
		}
		else
		{
			OnResetDevice();

			//Log
			Log("DXGraphicEngine::Resize() Device Rollbacked");
		}

		return FALSE;
	}

	//Save new mode
	//SETTINGSHANDLER->Set(!Settings::GetInstance()->GetCFG()->bFullscreen, screenWidth, screenHeight);

	InitRender();
	//Reset Device
	OnResetDevice();

	//Log
	Log("DXGraphicEngine::Resize() Device Reset");

	return TRUE;
}

BOOL DXGraphicEngine::SaveRenderTargetToFile(const char* pszFilePath)
{
	//Get Render Target
	LPDIRECT3DSURFACE9 lpRenderTarget;
	if (FAILED(hr = lpD3DDev->GetRenderTarget(0, &lpRenderTarget)))
	{
		Log("Screenshot(): GetRenderTarget Failed");

		return FALSE;
	}

	//Save to File
	BOOL bRet = SUCCEEDED(hr = D3DXSaveSurfaceToFileA(pszFilePath, D3DXIFF_PNG, lpRenderTarget, NULL, NULL));

	//Log if Fail
	if (!bRet)
		Log("Screenshot(): D3DXSaveSurfaceToFileA Failed");

	//Clean up
	RELEASE(lpRenderTarget);

	return bRet;
}

UINT DXGraphicEngine::GetVideoMemory()
{
	if (lpD3DDev)
		return lpD3DDev->GetAvailableTextureMem();

	return 0;
}

std::string DXGraphicEngine::GetVideoName()
{
	D3DADAPTER_IDENTIFIER9 s;

	if (FAILED(lpD3D->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &s)))
		return "";

	return std::string(s.Description);
}

UINT DXGraphicEngine::GetVertexSize(DWORD dwVertexTypeDesc)
{
	UINT uVertexSize = 0;

	//Get Vertex Size
	if (dwVertexTypeDesc == 324)
		uVertexSize = 28;
	else if (dwVertexTypeDesc == 452)
		uVertexSize = sizeof(EXEDrawVertex);
	else if (dwVertexTypeDesc == 708)
		uVertexSize = sizeof(EXEDrawVertex) + 8;
	else if (dwVertexTypeDesc == 964)
		uVertexSize = sizeof(EXEDrawVertex) + 16;
	else if (dwVertexTypeDesc == 1220)
		uVertexSize = sizeof(EXEDrawVertex) + 24;

	return uVertexSize;
}

