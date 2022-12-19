#pragma once

#include "sinbaram/sinInterFace.h"
#include "character.h"
#include "playmain.h"
#include "netplay.h"
#include "Chronos/Engine/DirectX/DXGraphicEngine.h"
#include "Settings/Settings.h"


#define ISSHOW_MINIMAP cInterFace.sInterFlags.MapOnFlag
#define UNITDATA lpCurPlayer

#define RESOLUTION_WIDTH smScreenWidth
#define RESOLUTION_HEIGHT smScreenHeight

#define BMPImage			unsigned int
#define TGAImage			unsigned int
#define UNKNOWN				DWORD
#define	PI					3.14159265358979323846f

#define RELEASE(p)			{ if(p != NULL) p->Release(); p = NULL;}
#define INIT(p)				{ if(p != NULL) p->Init();}
#define INITP(p, ptr)		{ if(p != NULL && ptr != NULL) p->Init(ptr);}
#define DELET(p)			{ if(p != NULL) delete p; p = NULL;}
#define DELETA(p)			{ if(p != NULL) delete[] p; p = NULL;}
#define SHUTDOWN(p)			{ if(p != NULL) p->Shutdown();}
#define ADDREF(p)			{ if(p != NULL) p->AddRef();}
#define CLEARPTR(p)			{ if(p != NULL) p->Clear();}
#define RESETPTR(p)			{ if(p != NULL) p.reset(); p = NULL;}

enum EPTAngle : int
{
	PTANGLE_360 = 4096,
	PTANGLE_1 = (PTANGLE_360 / 360),
	PTANGLE_45 = (PTANGLE_360 / 8),
	PTANGLE_90 = (PTANGLE_360 / 4),
	PTANGLE_180 = (PTANGLE_360 / 2),
	PTANGLE_270 = (PTANGLE_180 + PTANGLE_90),
	PTANGLE_Mask = (PTANGLE_360 - 1),
};
