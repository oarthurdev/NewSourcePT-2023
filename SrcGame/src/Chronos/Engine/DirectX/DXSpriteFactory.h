#pragma once

#include "DXSprite.h"
#include <memory>
#include <vector>

namespace DX
{
	class GraphicsDevice;

	typedef std::shared_ptr<class SpriteFactory> SpriteFactory_ptr;

	class SpriteFactory
	{
	public:
		SpriteFactory(GraphicsDevice* pGraphicsDevice);

		void OnLostDevice();
		void OnResetDevice();

		Sprite_ptr MakeSprite(BOOL bSharable);

	private:
		GraphicsDevice* pGraphicsDevice;

		std::vector<Sprite_ptr> vCache;
	};
}
