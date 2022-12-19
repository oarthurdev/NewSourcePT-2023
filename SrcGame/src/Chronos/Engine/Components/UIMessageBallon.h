#pragma once

#include "UIImage.h"
#include "UIText.h"
#include <memory>
#include <vector>

struct EXETextureHandle
{
	char szName[64];
	char szNameA[64];

	LPDIRECT3DTEXTURE9 pcD3DTexture;

	int iWidth;
	int iHeight;

	int iUseCounter;

	int iTransparency;

	BOOL bSwap;
};

struct EXESurfaceOld
{
	int iReferenceCount;
	EXETextureHandle sTexture;
	void* psCache;
};

enum ESkinID
{
	SKINID_Undefined = -1,

	SKINID_Normal,
	SKINID_Blue,
	SKINID_Green,
};

namespace UI
{
	struct Balloon
	{
		class Image* pImageLeftTop;
		class Image* pImageMiddleTop;
		class Image* pImageRightTop;
		class Image* pImageLeft;
		class Image* pImageRight;
		class Image* pImageLeftBottom;
		class Image* pImageMiddleBottom;
		class Image* pImageRightBottom;
		class Image* pImageTailBottom;
		class Image* pImageCenter;
	};

	enum EPositionText
	{
		POSITIONTEXT_Top,
		POSITIONTEXT_Middle,
		POSITIONTEXT_Bottom,
	};

	struct ExtraText
	{
		Text_ptr pText;
		EPositionText ePosition;
	};

	typedef std::shared_ptr<class MessageBalloon> MessageBallon_ptr;
	class MessageBalloon : public Element
	{
	public:
		//Constructor
		MessageBalloon(Rectangle2D rRectangle);
		virtual ~MessageBalloon();

		void Init();

		void SetMessage(std::string strMessage);
		void SetClanName(std::string strText);
		void SetPetName(std::string strText, DWORD dwColor = -1);
		void AddExtraText(int iID, EPositionText ePosition, std::string strText, DWORD dwColor = -1);
		void ResetMessage();
		Text_ptr GetTextMessage() { return pTextMessage; }

		void Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY);

		void SetHover(BOOL b) { bHover = b; }
		void SetColor(DWORD dwColor);

		void IsCharacterMessage(BOOL b);
		void SetSkin(ESkinID e) { eSkinID = e; }

		void SetBellatraIconID(int i) { iBellatraCrown = i; }

		void SetClanIconTexture(EXESurfaceOld* ps);

		void DrawMessageBalloonBox(int iX, int iY, int iWidth, int iHeight);
	protected:
		Balloon saMessagesBalloon[3][2];
		ESkinID eSkinID = SKINID_Normal;

		BOOL bHover = FALSE;
		BOOL bIsMessage = FALSE;
		BOOL bIsCharacterMessage = FALSE;
		BOOL bClanName = FALSE;
		BOOL bPetName = FALSE;

		Text_ptr pTextMessage;
		Text_ptr pTextClanName;
		Text_ptr pTextPetName;
		std::vector<ExtraText*> vExtraText;

		BOOL bShowClanIcon = FALSE;
		EXESurfaceOld* psTextureClanIcon;

		int iBellatraCrown = -1;
		class Image* pcaBellatraCrown[3];
	};
};