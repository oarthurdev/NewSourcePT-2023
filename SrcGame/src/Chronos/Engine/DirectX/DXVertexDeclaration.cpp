
#include "DXVertexDeclaration.h"
#include "def.h"

namespace DX
{

	VertexDeclaration::VertexDeclaration(LPDIRECT3DVERTEXDECLARATION9 lpVertexDeclaration) : lpVertexDeclaration(lpVertexDeclaration)
	{
		ADDREF(lpVertexDeclaration);
	}

	VertexDeclaration::~VertexDeclaration()
	{
		RELEASE(lpVertexDeclaration);
	}

}