#pragma once

#include <Windows.h>

#define PI 3.14159265358979323846f

#define TICKCOUNT GetTickCount()


#define RELEASE(p) { if(p != NULL) p->Release(); p = NULL;}
#define INIT(p) { if(p != NULL) p->Init();}
#define INITP(p, ptr) { if(p != NULL && ptr != NULL) p->Init(ptr);}
#define DELET(p) { if(p != NULL) delete p; p = NULL;}
#define DELETA(p) { if(p != NULL) delete[] p; p = NULL;}
#define SHUTDOWN(p) { if(p != NULL) p->Shutdown();}
#define ADDREF(p) { if(p != NULL) p->AddRef();}
#define CLEARPTR(p) { if(p != NULL) p->Clear();}
#define RESETPTR(p) { if(p != NULL) p.reset(); p = NULL;}

//#define ISPRESSEDKEY(c) (*(BYTE*)(0x00A16318 + c))