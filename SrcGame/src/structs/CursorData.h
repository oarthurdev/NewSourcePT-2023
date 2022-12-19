#ifndef CursorData_H
#define CursorData_H

#include <Windows.h>

struct CursorData
{
	int iID;

	HCURSOR hCursor;

	CursorData(int i, HCURSOR h) { iID = i; hCursor = h; };

	~CursorData() {};
};

#endif // CursorData_H
