#pragma once

#include "DXEffect.h"
#include "DXTexture.h"
#include <string>
#include <vector>

namespace DX
{

	const auto MAX_MATERIAL_TEXTURES = 8;

	typedef std::shared_ptr<class Material> Material_ptr;

	class Material
	{
	public:
		enum EType : int
		{
			TYPE_Normal = 0,

			TYPE_Water = 1,
		};

		enum EAlphaBlend : int
		{
			ALPHABLEND_None = 0,
			ALPHABLEND_Alpha = 1,
			ALPHABLEND_Additive = 2,
			ALPHABLEND_InverseShadow = 3,
			ALPHABLEND_AddColor = 4,
			ALPHABLEND_Shadow = 5,
			ALPHABLEND_Color = 6,
		};

		enum ETextureType : int
		{
			TEXTURETYPE_None = 0,

			TEXTURETYPE_Reflective = 1,

			TEXTURETYPE_Scroll1 = 2,
			TEXTURETYPE_Scroll2 = 3,
			TEXTURETYPE_Scroll3 = 4,
			TEXTURETYPE_Scroll4 = 5,
			TEXTURETYPE_Scroll5 = 6,
			TEXTURETYPE_Scroll6 = 7,
			TEXTURETYPE_Scroll7 = 8,
			TEXTURETYPE_Scroll8 = 9,
			TEXTURETYPE_Scroll9 = 10,
			TEXTURETYPE_Scroll10 = 11,

			TEXTURETYPE_ScrollSlow1 = 12,
			TEXTURETYPE_ScrollSlow2 = 13,
			TEXTURETYPE_ScrollSlow3 = 14,
			TEXTURETYPE_ScrollSlow4 = 15,
		};

	public:
		Material();
		virtual ~Material();

		void SetEffect(Effect_ptr _pEffect) { pEffect = _pEffect; }
		Effect_ptr GetEffect() { return pEffect; }

		void SetEffectTechnique(const std::string& _strEffectTechnique) { strEffectTechnique = _strEffectTechnique; }
		const std::string& GetEffectTechnique() const { return strEffectTechnique; }

		void SetEffectNumPasses(UINT _uEffectNumPasses) { uEffectNumPasses = _uEffectNumPasses; }
		UINT GetEffectNumPasses() const { return uEffectNumPasses; }

		void AddTexture(Texture_ptr pTexture, ETextureType eTextureType) { vTextures.push_back(pTexture); vTextureTypes.push_back(eTextureType); }

		const std::vector<Texture_ptr> GetTextures() const { return vTextures; }
		const std::vector<ETextureType> GetTextureTypes() const { return vTextureTypes; }

		void SetTwoSided(BOOL b) { bTwoSided = b; }
		BOOL GetTwoSided() const { return bTwoSided; }

		void SetDiffuseRed(float r) { fDiffuseRed = r; }
		float GetDiffuseRed() const { return fDiffuseRed; }

		void SetDiffuseGreen(float g) { fDiffuseGreen = g; }
		float GetDiffuseGreen() const { return fDiffuseGreen; }

		void SetDiffuseBlue(float b) { fDiffuseBlue = b; }
		float GetDiffuseBlue() const { return fDiffuseBlue; }

		void SetTransparency(float b) { fTransparency = b; }
		float GetTransparency() const { return fTransparency; }

		void SetSelfIllumination(float f) { fSelfIllumination = f; }
		float GetSelfIllumination() const { return fSelfIllumination; }

		void SetTransparent(BOOL b) { bIsTransparent = b; }
		BOOL GetTransparent() const { return bIsTransparent; }

		void SetInvisible(BOOL b) { bIsInvisible = b; }
		BOOL GetInvisible() const { return bIsInvisible; }

		void SetAlphaBlend(EAlphaBlend e) { eAlphaBlend = e; }
		EAlphaBlend GetAlphaBlend() const { return eAlphaBlend; }

	private:
		Effect_ptr pEffect;
		std::string strEffectTechnique;
		UINT uEffectNumPasses = 1;

		std::vector<Texture_ptr> vTextures;
		std::vector<ETextureType> vTextureTypes;

		BOOL bTwoSided = FALSE;

		float fDiffuseRed = 0.0f, fDiffuseGreen = 0.0f, fDiffuseBlue = 0.0f;
		float fTransparency = 0.0f;
		float fSelfIllumination = 0.0f;

		BOOL bIsTransparent = FALSE;
		BOOL bIsInvisible = FALSE;

		EAlphaBlend eAlphaBlend = ALPHABLEND_Alpha;
	};

}