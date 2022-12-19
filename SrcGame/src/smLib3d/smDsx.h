#ifndef _SMDSX_H_
#define _SMDSX_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <Shlwapi.h>

#pragma comment(lib, "d3d9.lib") 
#pragma comment(lib, "d3dx9.lib") 
#pragma comment( lib, "winmm.lib" )
#pragma comment(lib, "shlwapi.lib")

struct D3DTLVERTEX
{
	float sx;
	float sy;
	float sz;
	float rhw;
	D3DCOLOR color;
	D3DCOLOR specular;
	float tu;
	float tv;
};

extern int smFlipCount;
extern bool MagFilter;
extern int WindowMode;
extern int smTextureBPP;

extern int smScreenWidth, smScreenHeight;


void InitRender();
void DrawTexture(LPDIRECT3DTEXTURE9 Texture, D3DTLVERTEX* Vertex, int AlphaBlend);
void DrawTexture2D(LPDIRECT3DTEXTURE9 lpTexture, RECT destinationRect, RECT sourceRect, int alphaBlend);

extern int MESSAGE(char* t);

typedef struct {
	float r, g, b, a;
} COLORVALUE, * LPCOLORVALUE;

typedef struct {
	float	x, y, z;
} VECTOR, * LPVECTOR;

typedef struct {
	float   tu, tv;
} TVERTEX, * LPTVERTEX;







#endif
