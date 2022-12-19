#pragma once

#include "Geometry.h"
#include <d3d9.h>

struct EXEDrawVertex
{
	float x;
	float y;
	float z;
	float rhw;
	unsigned long d3dColor;
	unsigned long d3dSpecular;
	float u;
	float v;
};

struct EXEColoredVertex
{
	float x;
	float y;
	float z;
	unsigned long d3dcolor;
};

struct EXEDrawVertexModel
{
	float x;
	float y;
	float z;
	unsigned long d3dColor;
	unsigned long d3dSpecular;
};

struct EXEDrawVertexModelCoord
{
	float u;
	float v;
};

struct EXEDrawVertexMinor
{
	float x;
	float y;
	float z;
	float rhw;
	unsigned long d3dColor;
	float u;
	float v;
};

struct EXEVertex
{
	Point3D sPosition;
	Point3D sPosition2;
};

struct EXED3DVECTOR4D
{
	float fX;
	float fY;
	float fZ;
	float fW;
};