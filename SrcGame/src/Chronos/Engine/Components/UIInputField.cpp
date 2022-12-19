
#include "UIInputField.h"
#include "UIElement.h"
#include "UIImageLoader.h"
#include "UIImageRender.h"
#include "UIEvent.h"
#include "DXFont.h"
#include "DXGraphicEngine.h"
#include "Keyboard/Keyboard.h"
#include "Utils/String.h"
#include "Utils/Macros.h"
#include "Utils/_common.h"
#include <string>
#include <sstream>
#include <algorithm>

namespace UI
{
	InputField::InputField(Rectangle2D rRectangle) : Element(rRectangle)
	{
	}

	InputField::~InputField()
	{
	}

	void InputField::Clear()
	{
		CLEARPTR(pImage);
		UI::ImageLoader::DeleteImage(pImage);

		vInputActions.clear();
		vBindActionsKeyboard.clear();
	}

	std::string InputField::GetText()
	{
		if (bIsNumber && (strText.length() == 0 || atoi(strText.c_str()) == 0))
			return "0";

		return strText;
	}

	void InputField::SetIsNumber(BOOL b, int iMin, int iMax)
	{
		bIsNumber = b;
		iMinNum = iMin;
		iMaxNum = iMax;
		SetText(FormatString("%d", iMin));
	};

	void InputField::Update(float fTime)
	{
	}

	UINT InputField::BuildFormat() const
	{
		UINT uFormat = DT_EXPANDTABS;

		switch (eHorizontalAlign)
		{
		default:
		case ALIGN_Left:
			uFormat |= DT_LEFT;
			break;
		case ALIGN_Center:
			uFormat |= DT_CENTER;
			break;
		case ALIGN_Right:
			uFormat |= DT_RIGHT;
			break;
		}

		switch (eVerticalAlign)
		{
		default:
		case ALIGN_Top:
			uFormat |= DT_TOP;
			break;
		case ALIGN_Middle:
			uFormat |= DT_VCENTER;
			break;
		case ALIGN_Bottom:
			uFormat |= DT_BOTTOM;
			break;
		}

		return uFormat;
	}

	void InputField::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (IsOpen())
		{
			int iRenderX = GetX() + iX;
			int iRenderY = GetY() + iY;
			int iRenderWidth = bParentChild ? low(GetWidth(), iWidth - GetX()) : GetWidth();
			int iRenderHeight = bParentChild ? low(GetHeight(), iHeight - GetY()) : GetHeight();

			UI::ImageRender::Render(pImage, iRenderX + iSourceX, iRenderY + iSourceY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);

			int iWidthSelectedText = FONTHANDLER->GetWidthText(iFontHandler, strText.c_str(), uCurrPosition);
			int iWidthText = FONTHANDLER->GetWidthText(iFontHandler, strText.c_str(), strText.length());

			bool bClipText = GetWidth() - iWidthSelectedText < 0 ? true : false;

			RECT rRectT;
			rRectT.left = bClipText ? iRenderX - 10 - (iWidthSelectedText - GetWidth()) : iRenderX;
			rRectT.top = iRenderY;
			rRectT.right = rRectT.left + GetWidth();
			rRectT.bottom = rRectT.top + GetHeight();

			if (eHorizontalAlign == ALIGN_Left)
				rRectT.left += 2;

			//Compute Scissor
			{
				RECT r = RECT{ iRenderX, iRenderY, iRenderX + GetWidth(), iRenderY + GetHeight() };
				GRAPHICENGINE->GetGraphicsDevice()->GetScissorRectInside(r);
				GRAPHICENGINE->GetGraphicsDevice()->PushScissorRect(r);
			}
			FONTHANDLER->Draw(iFontHandler, rRectT, strText, BuildFormat() | DT_NOCLIP, dwColorText);

			if (bHover || bSelect)
			{
				if (pGroupMain)
				{
					if (pGroupMain->GetIndexObject() != GetID())
						bSelect = FALSE;

					if (bSelect)
					{
						if (dwTimeBarText < GetCurrentTime())
						{
							dwTimeBarText = GetCurrentTime() + iBarTextTime;
							bBarTextShow = bBarTextShow ? FALSE : TRUE;
						}
						else
						{
							if (bBarTextShow)
							{
								rRectT.left += iWidthSelectedText;
								FONTHANDLER->Draw(iFontHandler, rRectT, "|", BuildFormat() | DT_NOCLIP, dwColorText);
							}
						}

						if (strText.length() > 0)
						{
							//Render Selected Text
							if (iSelectedTextLength > 0)
							{
								int iWidthText = FONTHANDLER->GetWidthText(iFontHandler, strText.substr(iSelectedTextPos, iSelectedTextLength).c_str(), iSelectedTextLength);
								GRAPHICENGINE->DrawRectangle2D(Rectangle2D(iRenderX + sSelectedTextBox.iX, iRenderY + sSelectedTextBox.iY, iWidthText, 14), D3DCOLOR_ARGB(100, 255, 255, 255));
							}
							else if (iSelectedTextLength < 0)
							{
								int iWidthText = FONTHANDLER->GetWidthText(iFontHandler, strText.substr(iSelectedTextPos - abs(iSelectedTextLength), iSelectedTextPos + 1).c_str(), abs(iSelectedTextLength));
								GRAPHICENGINE->DrawRectangle2D(Rectangle2D(iRenderX + sSelectedTextBox.iX - iWidthText + sSelectedTextBox.iWidth, iRenderY + sSelectedTextBox.iY, iWidthText, 14), D3DCOLOR_ARGB(100, 255, 255, 255));
							}
						}
					}
				}
			}

			GRAPHICENGINE->GetGraphicsDevice()->PopScissorRect();

			Element::Render(iX, iY, iWidth, iHeight, iSourceX, iSourceY);
		}
	}

	void InputField::OnMouseMove(CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		//Text selected?
		if (iSelectedTextPos > 0 && bSelectingText)
		{
			//Mouse Position
			Point2D* psPosition = pcMouse->GetPosition();

			int iDifference = psPosition->iX - (sSelectedTextBox.iX + GetX() + iX);
			int iCurrentWidth = 0;

			if (iDifference > 0)
			{
				for (size_t i = iSelectedTextPos; i < strText.length() + 1; i++)
				{
					char c = strText[i];
					iCurrentWidth += FONTHANDLER->GetWidthText(iFontHandler, &c, 1);

					if (iCurrentWidth > iDifference)
					{
						iSelectedTextLength = i - iSelectedTextPos + 1;
						break;
					}
				}
			}
			else if (iDifference < 0)
			{
				for (size_t i = iSelectedTextPos; i > 0; i--)
				{
					char c = strText[i];
					iCurrentWidth += FONTHANDLER->GetWidthText(iFontHandler, &c, 1);

					if (iCurrentWidth > abs(iDifference))
					{
						iSelectedTextLength = i - iSelectedTextPos - 1;
						break;
					}
				}
			}
		}
	}

	BOOL InputField::OnMouseClick(CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || bDisable)
			return FALSE;

		if (ClickDownL != pcMouse->GetEvent())
		{
			bSelectingText = FALSE;
			return FALSE;
		}

		//Mouse Position
		Point2D* psPosition = pcMouse->GetPosition();

		int iRenderX = GetX() + iX + iSourceX;
		int iRenderY = GetY() + iY + iSourceX;
		int iRenderWidth = bParentChild ? low(GetWidth(), iWidth - GetX()) : GetWidth();
		int iRenderHeight = bParentChild ? low(GetHeight(), iHeight - GetY()) : GetHeight();

		Rectangle2D rInput = { iRenderX, iRenderY, iRenderWidth, iRenderHeight };
		sSelectedTextBox = { 0, 0, 0, 0 };
		iSelectedTextPos = 0;
		iSelectedTextLength = 0;
		bSelectingText = FALSE;

		//Inside Input?
		if (rInput.Inside(psPosition))
		{
			if (bSelectType)
			{
				if (pGroupMain)
				{
					if (!bSelect)
						pGroupMain->SetIndexObject(GetID());
					else
					{
						uCurrPosition = strText.length();

						Rectangle2D sTextBox = { iRenderX, iRenderY, iRenderX + GetWidth(), iRenderY + GetHeight() };
						int iCurrentWidthAdd = 0;

						//Loop Text
						for (size_t i = 0; i < strText.length(); i++)
						{
							char c = strText[i];
							int iCharacterWidth = FONTHANDLER->GetWidthText(iFontHandler, &c, 1);
							int iCharacterHeight = FONTHANDLER->GetHeightText(iFontHandler, &c, RECT{ 0,0,0,0 });

							Rectangle2D sDetectBox = { sTextBox.iX + iCurrentWidthAdd + 2, sTextBox.iY + 2, iCharacterWidth, iCharacterHeight };
							sSelectedTextBox = { iCurrentWidthAdd + 2, 2, iCharacterWidth, iCharacterHeight };

							//Mouse inside letter bounding box?
							if (sDetectBox.Inside(psPosition))
							{
								bSelectingText = TRUE;
								uCurrPosition = i;
								iSelectedTextPos = i + 1;
								break;
							}

							bSelectingText = TRUE;
							uCurrPosition = strText.length();
							iSelectedTextPos = strText.length();

							iCurrentWidthAdd += iCharacterWidth;
						}
					}

					bSelect = TRUE;
				}
				else
					bSelect = bSelect ? FALSE : TRUE;
			}
			return TRUE;
		}

		return FALSE;
	}

	BOOL InputField::OnMouseScroll(class CMouse* pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen())
			return FALSE;

		Point2D* psPosition = pcMouse->GetPosition();

		if (bSelect)
		{
			if (bIsNumber && GetCanScroll())
			{
				int iNum = atoi(strText.c_str()) + pcMouse->GetDistance();
				if (iNum > iMaxNum)
					iNum = iMaxNum;

				if (iNum < iMinNum)
					iNum = iMinNum;

				strText = FormatString("%d", iNum);

				return TRUE;
			}
		}
		return FALSE;
	}

	BOOL InputField::OnKeyPress(class CKeyboard* pcKeyboard)
	{
		if (bSelect)
		{
			if (pcKeyboard->GetEvent() == KeyDown)
			{
				for (size_t i = 0; i < vBindActionsKeyboard.size(); i++)
				{
					if (pcKeyboard->GetKey() == vBindActionsKeyboard[i].dwKey)
					{
						UI::Event::Invoke(vBindActionsKeyboard[i].iEventID);
						return TRUE;
					}
				}
			}

			if (pcKeyboard->GetKey() == VK_RETURN && pcKeyboard->GetEvent() == KeyDown)
			{
				iSelectedTextLength = 0;
				bSelect = FALSE;
				return TRUE;
			}

			//Have a text?
			if (strText.length() > 0)
			{
				if (pcKeyboard->GetKey() == VK_RIGHT && pcKeyboard->GetEvent() == KeyDown)
				{
					if ((UINT)uCurrPosition < strText.length())
						uCurrPosition++;
				}
				else if (pcKeyboard->GetKey() == VK_LEFT && pcKeyboard->GetEvent() == KeyDown)
				{
					if (uCurrPosition > 0)
						uCurrPosition--;
				}
				else if ((pcKeyboard->GetKey() == VK_HOME || pcKeyboard->GetKey() == VK_PRIOR) && pcKeyboard->GetEvent() == KeyDown)
				{
					uCurrPosition = 0;
					return TRUE;
				}
				else if ((pcKeyboard->GetKey() == VK_END || pcKeyboard->GetKey() == VK_NEXT) && pcKeyboard->GetEvent() == KeyDown)
				{
					uCurrPosition = strText.length();
					return TRUE;
				}
				else if (pcKeyboard->GetKey() == VK_DELETE && pcKeyboard->GetEvent() == KeyDown)
				{
					if (iSelectedTextLength > 0 && strText.length() > 0 && (UINT)iSelectedTextLength <= strText.length())
					{
						strText.erase(iSelectedTextPos - 1, iSelectedTextLength);
						iSelectedTextPos = 0;
						iSelectedTextLength = 0;
					}
					else if ((UINT)abs(iSelectedTextLength) <= strText.length() && iSelectedTextLength < 0 && strText.length() > 0)
					{
						strText.erase(iSelectedTextPos - abs(iSelectedTextLength), abs(iSelectedTextLength));
						uCurrPosition -= abs(iSelectedTextLength);
						iSelectedTextPos = 0;
						iSelectedTextLength = 0;
					}
					else if (strText.length() > 0 && uCurrPosition > 0 && (UINT)uCurrPosition <= strText.length())
					{
						strText.erase(uCurrPosition, 1);
					}

					return TRUE;
				}
			}

			return TRUE;
		}

		return FALSE;
	}

	BOOL InputField::OnKeyChar(class CKeyboard* pcKeyboard)
	{
		if (bSelect)
		{
			if (pcKeyboard->GetChar() == VK_BACK)
			{
				if (iSelectedTextLength > 0 && strText.length() > 0 && (UINT)iSelectedTextLength <= strText.length())
				{
					strText.erase(iSelectedTextPos - 1, iSelectedTextLength);
					iSelectedTextPos = 0;
					iSelectedTextLength = 0;
				}
				else if ((UINT)abs(iSelectedTextLength) <= strText.length() && iSelectedTextLength < 0 && strText.length() > 0)
				{
					strText.erase(iSelectedTextPos - abs(iSelectedTextLength), abs(iSelectedTextLength));
					uCurrPosition -= abs(iSelectedTextLength);
					iSelectedTextPos = 0;
					iSelectedTextLength = 0;
				}
				else if (strText.length() > 0 && uCurrPosition > 0 && (UINT)uCurrPosition <= strText.length())
				{
					strText.erase(uCurrPosition - 1, 1);
					uCurrPosition--;
				}

				return TRUE;
			}
			else if (pcKeyboard->GetChar() == VK_TAB)
			{
				return TRUE;
			}
			else if (pcKeyboard->IsKeyDown(VK_CONTROL) && pcKeyboard->IsKeyDown('V'))
			{
				AddInput(GetClipboardText());
				return TRUE;
			}
			else if (pcKeyboard->IsKeyDown(VK_CONTROL) && pcKeyboard->IsKeyDown('C'))
			{
				if (iSelectedTextLength > 0 && strText.length() > 0 && (UINT)iSelectedTextLength <= strText.length())
				{
					SetClipboardText((char*)strText.substr(iSelectedTextPos - 1, iSelectedTextLength).c_str());
					iSelectedTextPos = 0;
					iSelectedTextLength = 0;
				}
				else if ((UINT)abs(iSelectedTextLength) <= strText.length() && iSelectedTextLength < 0 && strText.length() > 0)
				{
					SetClipboardText((char*)strText.substr(iSelectedTextPos - abs(iSelectedTextLength), abs(iSelectedTextLength)).c_str());
					uCurrPosition -= abs(iSelectedTextLength);
					iSelectedTextPos = 0;
					iSelectedTextLength = 0;
				}

				return TRUE;
			}
			else if (pcKeyboard->IsKeyDown(VK_SHIFT) && pcKeyboard->IsKeyDown(VK_ESCAPE))
				return TRUE;
			else if (pcKeyboard->IsKeyDown(VK_CONTROL) && pcKeyboard->IsKeyDown('Z'))
			{
				UndoAction();
				return TRUE;
			}
			else if (pcKeyboard->IsKeyDown(VK_CONTROL) && pcKeyboard->IsKeyDown('A'))
			{
				int iCharacterWidth = FONTHANDLER->GetWidthText(iFontHandler, strText.c_str(), 1);
				int iCharacterHeight = FONTHANDLER->GetHeightText(iFontHandler, strText.c_str(), RECT{ 0, 0, 0, 0 });

				sSelectedTextBox = { 2, 2, iCharacterWidth, iCharacterHeight };

				iSelectedTextPos = 1;
				iSelectedTextLength = strText.length();
				uCurrPosition = 0;
				return TRUE;
			}
			else if (pcKeyboard->GetChar() == VK_SPACE)
			{
				AddInput(" ");
				return TRUE;
			}
			else if (strText.length() < (UINT)iTextLength)
			{
				//if ( pcKeyboard->IsKeyDown( VK_CONTROL ) == FALSE )
				{
					std::stringstream ss;
					std::string s;
					char c = pcKeyboard->GetChar();

					ss << c;
					ss >> s;

					int iNumOld = atoi(strText.c_str());

					AddInput(s);

					int iNumNew = atoi(strText.c_str());

					if (bIsNumber)
					{
						if (bIsNumber && strText.length() > 1 && atoi(strText.c_str()) == 0)
							strText = "";

						if (iNumOld == 0 && iNumNew < 10)
							strText = s;

						if (atoi(strText.c_str()) > iMaxNum)
							strText = FormatString("%d", iMaxNum);
					}
				}
			}
			return TRUE;
		}
		return FALSE;
	}

	void InputField::ClearInput()
	{
		iSelectedTextLength = 0;
		uCurrPosition = 0;
		strText.clear();
	}

	void InputField::SetFont(const char* pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold, DWORD dwColor)
	{
		iFontHandler = FONTHANDLER->CreateFont(pszFont, iHeight, iWidth, bItalic, bBold, -1);
		iFontHeight = iHeight;
		dwColorText = dwColor;
	}

	void InputField::UndoAction()
	{
		std::string strLastAction = vInputActions[vInputActions.size() - 1];
		std::size_t uPosition = strText.rfind(strLastAction);

		if (uPosition != std::string::npos && strLastAction.length() > 0)
		{
			uCurrPosition -= strLastAction.length();
			strText.erase(uPosition, strLastAction.length());
			vInputActions.pop_back();
		}
	}

	void InputField::AddInput(std::string str)
	{
		if (strText.length() >= (UINT)iTextLength)
			return;

		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
		str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());

		if (bIsNumber)
		{
			for (UINT i = 0; i < str.length(); i++)
			{
				char c = str.c_str()[i];

				if (c < 0x30 || c > 0x39)
					return;
			}
		}

		if (bAllowedRule)
		{
			BOOL bFound = FALSE;

			for (UINT i = 0; i < str.length(); i++)
			{
				char c = str.c_str()[i];

				if (bAllowedRule)
				{
					bFound = FALSE;

					for (auto v : strAllowed)
					{
						if (v == c)
						{
							bFound = TRUE;
							break;
						}
					}

					if (bFound == FALSE)
						return;
				}
			}
		}

		std::string strNew = "";

		if (strText.length() + str.length() > (UINT)iTextLength)
			strNew = str.substr(0, (strText.length() + str.length()) - iTextLength);
		else
			strNew = str;

		if ((UINT)uCurrPosition <= strText.length())
		{
			strText.insert(uCurrPosition, strNew);
			uCurrPosition += strNew.length();

			vInputActions.push_back(strNew);
		}
	}
}