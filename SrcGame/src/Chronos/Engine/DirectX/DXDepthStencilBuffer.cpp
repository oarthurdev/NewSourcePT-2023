#include "DXDepthStencilBuffer.h"
#include "DXGraphicsDevice.h"
#include "Utils/Macros.h"
#include <memory>

namespace DX
{

	DepthStencilBuffer::DepthStencilBuffer(std::weak_ptr<GraphicsDevice> pGraphicsDevice, int iSharableID, UINT uSizeShiftRight) : pGraphicsDevice(pGraphicsDevice), iSharableID(iSharableID), uSizeShiftRight(uSizeShiftRight)
	{
		lpSurface = NULL;
	}

	DepthStencilBuffer::DepthStencilBuffer(std::weak_ptr<GraphicsDevice> pGraphicsDevice, int iSharableID, UINT uWidth, UINT uHeight) : pGraphicsDevice(pGraphicsDevice), iSharableID(iSharableID), uSizeShiftRight(0), uWidth(uWidth), uHeight(uHeight)
	{
	}

	DepthStencilBuffer::~DepthStencilBuffer()
	{
		RELEASE(lpSurface);
	}

	void DepthStencilBuffer::OnLostDevice()
	{
		RELEASE(lpSurface);
	}

	void DepthStencilBuffer::OnResetDevice()
	{
		pGraphicsDevice.lock()->BuildDepthStencilBuffer(shared_from_this());
	}

}