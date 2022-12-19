#pragma once

#include "DXEffect.h"
#include <string>
#include <vector>
#include <memory>

namespace DX
{

	class GraphicsDevice;

	typedef std::shared_ptr<class EffectFactory> EffectFactory_ptr;

	class EffectFactory
	{
	public:
		EffectFactory(GraphicsDevice* pGraphicsDevice);

		void OnLostDevice();
		void OnResetDevice();

		Effect_ptr MakeEffect(std::string strEffectFile);

		void ReloadEffects();

	private:
		LPD3DXEFFECT CreateEffectFromFile(std::string strEffectFile);

	private:
		GraphicsDevice* pGraphicsDevice;

		std::vector<Effect_ptr> vCache;
	};

}