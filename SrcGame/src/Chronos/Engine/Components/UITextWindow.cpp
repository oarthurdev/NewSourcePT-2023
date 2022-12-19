
#include "UITextWindow.h"
#include "DXFont.h"
#include "Utils/Macros.h"
#include <vector>
#include <string>

char szBufferTextWindow[8092];

namespace UI
{
	TextWindow::TextWindow(Rectangle2D rRectangle) : Element(rRectangle)
	{
	}

	TextWindow::~TextWindow()
	{
		for (std::vector<ParamsWindow*>::iterator it = vParams.begin(); it != vParams.end(); it++)
		{
			ParamsWindow* ps = (*it);

			DELET(ps);
		}

		vParams.clear();
	}

	void TextWindow::Clear()
	{
		for (std::vector<ParamsWindow*>::iterator it = vParams.begin(); it != vParams.end(); it++)
		{
			ParamsWindow* ps = (*it);

			DELET(ps);
		}

		vParams.clear();
	}

	void TextWindow::SetFont(const char* pszFont, int iHeight, int iWidth, BOOL bItalic, BOOL bBold, DWORD dwColor)
	{
		iFontHandler = FONTHANDLER->CreateFont(pszFont, iHeight, iWidth, bItalic, bBold, -1);
		dwColorText = dwColor;
	}

	void TextWindow::SetBox(Rectangle2D sBox)
	{
		rRect = sBox;
	}

	int TextWindow::GetHeightText()
	{
		int iRenderX = GetX();
		int iRenderY = GetY();

		return FONTHANDLER->GetHeightText(iFontHandler, strText.c_str(), { iRenderX, iRenderY, iRenderX + rRect.iWidth, rRect.iHeight + iRenderY });
	}

	void TextWindow::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		std::string strLocal = strText;

		// Parameters
		for (const auto& v : vParams)
		{
			std::size_t pos = strLocal.find(v->strParam);
			if (pos != std::string::npos)
				strLocal.replace(strLocal.begin() + pos, strLocal.begin() + pos + v->strParam.length(), v->strValue.begin(), v->strValue.end());
		}

		RECT rect{ iRenderX, iRenderY, iRenderX + rRect.iWidth, rRect.iHeight + iRenderY };

		FONTHANDLER->Draw(iFontHandler, rect, strLocal.c_str(), strLocal.length(), DT_WORDBREAK, dwColorText);
	}

	void TextWindow::SetParam(std::string strParam, std::string strValue)
	{
		for (const auto& v : vParams)
		{
			if (v->strParam.compare(strParam) == 0)
			{
				v->strValue = strValue;
				return;
			}
		}
		ParamsWindow* pParam = new ParamsWindow;
		pParam->strParam = strParam;
		pParam->strValue = strValue;
		vParams.push_back(pParam);
	}

	void TextWindow::LoadTextFromFile(const char* pszFile)
	{
		FILE* pFile = NULL;

		ZeroMemory(szBufferTextWindow, 8092);

		fopen_s(&pFile, pszFile, "rb");
		if (pFile)
		{
			fseek(pFile, 0, SEEK_END);
			int iSizeFile = ftell(pFile);
			fseek(pFile, 0, SEEK_SET);

			if (iSizeFile > 8092)
				iSizeFile = 8092;

			fread(szBufferTextWindow, iSizeFile, 1, pFile);
			fclose(pFile);
		}
		strText = szBufferTextWindow;
	}
}