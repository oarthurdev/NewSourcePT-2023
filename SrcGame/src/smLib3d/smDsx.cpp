#include "smDsx.h"
#include "smd3d.h"

#include "DXGraphicEngine.h"
#include "def.h"
#include <math.h>
#include <stdio.h>

extern HWND hwnd;

#define WINMODE	1

int smFlipCount = 0;
bool MagFilter = false;
int WindowMode = WINMODE;
int	smTextureBPP = 16;

int smScreenWidth, smScreenHeight;


int MESSAGE(char* t)
{
	FILE* fp;
	fp = fopen("error.log", "wb");
	if (fp != NULL) {
		fwrite(t, lstrlen(t), 1, fp);
		fclose(fp);
	}

	return NULL;
}


void InitRender()
{

	GRAPHICENGINE->StateSetup();

	/*if (GRAPHICDEVICE)
	{
		GRAPHICDEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);
		GRAPHICDEVICE->SetRenderState(D3DRS_CLIPPING, FALSE);
		GRAPHICDEVICE->SetRenderState(D3DRS_CULLMODE, 2);
		GRAPHICDEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);
		GRAPHICDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		GRAPHICDEVICE->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		GRAPHICDEVICE->SetRenderState(D3DRS_LASTPIXEL, FALSE);
		GRAPHICDEVICE->SetRenderState(D3DRS_DITHERENABLE, TRUE);
		GRAPHICDEVICE->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
		GRAPHICDEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		GRAPHICDEVICE->SetRenderState(D3DRS_ALPHAFUNC, D3DBLEND_DESTALPHA);
		GRAPHICDEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		GRAPHICDEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		GRAPHICDEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

		for (int cnt = 0; cnt < 8; cnt++)
		{
			GRAPHICDEVICE->SetSamplerState(cnt, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			GRAPHICDEVICE->SetSamplerState(cnt, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			GRAPHICDEVICE->SetSamplerState(cnt, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
			GRAPHICDEVICE->SetSamplerState(cnt, D3DSAMP_ADDRESSU, D3DTEXF_POINT);
			GRAPHICDEVICE->SetSamplerState(cnt, D3DSAMP_ADDRESSV, D3DTEXF_POINT);
			GRAPHICDEVICE->SetTexture(cnt, 0);
		}*/

	smRender.AlphaTestDepth = 60;
	smRender.dwMatDispMask = sMATS_SCRIPT_NOTVIEW;
	smRender.ZWriteAuto = FALSE;
	//}
}

extern DWORD smBackColor;

void DrawTexture(LPDIRECT3DTEXTURE9 Texture, D3DTLVERTEX* Vertex, int AlphaBlend)
{
	GRAPHICDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	GRAPHICDEVICE->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	GRAPHICDEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	if (AlphaBlend)
	{
		GRAPHICDEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		GRAPHICDEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		GRAPHICDEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	}
	else

	{
		GRAPHICDEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	}

	if (MagFilter)
	{
		GRAPHICDEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		GRAPHICDEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}
	else
	{
		GRAPHICDEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		GRAPHICDEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	}

	for (int cnt = 0; cnt < 8; cnt++)
		GRAPHICDEVICE->SetTexture(cnt, 0);
	GRAPHICDEVICE->SetTexture(0, Texture);
	GRAPHICDEVICE->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1);

	GRAPHICDEVICE->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, Vertex, sizeof(D3DTLVERTEX));
	if (!MagFilter)

	{
		GRAPHICDEVICE->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		GRAPHICDEVICE->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	}


	GRAPHICDEVICE->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	GRAPHICDEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
}

void DrawTexture2D(LPDIRECT3DTEXTURE9 lpTexture, RECT destinationRect, RECT sourceRect, int alphaBlend)
{
	auto width = RESOLUTION_WIDTH;
	auto height = RESOLUTION_HEIGHT;

	bool result = destinationRect.right > destinationRect.left;
	result &= destinationRect.bottom > destinationRect.top;
	result &= destinationRect.right >= 0;
	result &= destinationRect.bottom >= 0;
	result &= destinationRect.left < width;
	result &= destinationRect.top < height;
	result &= sourceRect.right > sourceRect.left;
	result &= sourceRect.bottom > sourceRect.top;

	//if (destinationRect.right > destinationRect.left
	//	&& destinationRect.bottom > destinationRect.top
	//	&& destinationRect.right >= 0
	//	&& destinationRect.bottom >= 0
	//	&& destinationRect.left < width
	//	&& destinationRect.top < height
	//	&& sourceRect.right > sourceRect.left
	//	&& sourceRect.bottom > sourceRect.top)

	if(result)
	{
		D3DSURFACE_DESC Desc;
		if (lpTexture)
			lpTexture->GetLevelDesc(0, &Desc);

		float u1, v1, u2, v2;

		if (lpTexture)
		{
			u1 = ((float)sourceRect.left + 0.5f) / Desc.Width;
			v1 = ((float)sourceRect.top + 0.5f) / Desc.Height;
			u2 = u1 + ((float)sourceRect.right - sourceRect.left) / Desc.Width;
			v2 = v1 + ((float)sourceRect.bottom - sourceRect.top) / Desc.Height;
		}
		else
		{
			u1 = 0.0f;
			v1 = 0.0f;
			u2 = 1.0f;
			v2 = 1.0f;
		}

		D3DTLVERTEX Vertices[4] =
		{
			{ (float)destinationRect.left, (float)destinationRect.top, 0.0f, 1.0f, D3DCOLOR_XRGB(255,255,255), 0, u1, v1 },
			{ (float)destinationRect.right, (float)destinationRect.top, 0.0f, 1.0f, D3DCOLOR_XRGB(255,255,255), 0, u2, v1 },
			{ (float)destinationRect.left, (float)destinationRect.bottom, 0.0f, 1.0f, D3DCOLOR_XRGB(255,255,255), 0, u1, v2 },
			{ (float)destinationRect.right,(float)destinationRect.bottom, 0.0f, 1.0f, D3DCOLOR_XRGB(255,255,255), 0, u2, v2 },
		};

		DrawTexture(lpTexture, Vertices, alphaBlend);
	}
}
