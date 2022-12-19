
#include "DXVertexBuffer.h"
#include "def.h"

namespace DX
{

	VertexBuffer::VertexBuffer(LPDIRECT3DVERTEXBUFFER9 lpVertexBuffer, UINT uElementSize, UINT uElementCount) : lpVertexBuffer(lpVertexBuffer), uElementSize(uElementSize), uElementCount(uElementCount)
	{
		ADDREF(lpVertexBuffer);
	}

	VertexBuffer::~VertexBuffer()
	{
		RELEASE(lpVertexBuffer);
	}

	void* VertexBuffer::Lock()
	{
		void* ptr;
		if (FAILED(lpVertexBuffer->Lock(0, 0, &ptr, 0)))
			return NULL;

		return ptr;
	}

	void VertexBuffer::Unlock()
	{
		lpVertexBuffer->Unlock();
	}

}