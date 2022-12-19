#include "UILinkerOld.h"

vector<LOADEDIMAGE*> vLoadedImages;

void ClearLoadedImages()
{
	vLoadedImages.clear();
}

LOADEDIMAGE* GetUIImage(char* path)
{
	for (auto pImage : vLoadedImages)
	{
		if (!lstrcmpi(pImage->ImagePath, path))
			return pImage;
	}
	return nullptr;
}

LPDIRECT3DTEXTURE9 LoadUIImage(char* path)
{
	LOADEDIMAGE* pImage = GetUIImage(path);
	if (pImage)
		return pImage->Image;

	pImage = new LOADEDIMAGE;
	if (pImage)
	{
		pImage->Image = LoadDibSurfaceOffscreen(path);
		lstrcpy(pImage->ImagePath, path);
		vLoadedImages.push_back(pImage);
		return pImage->Image;
	}

	return nullptr;
}

UIImageOld::UIImageOld(int iID, char* path, int x, int y, int w, int h)
{
	setID(iID);
	setX(x);
	setY(y);
	startX = 0;
	startY = 0;

	Image = LoadUIImage(path);

	if (Image)
	{
		D3DSURFACE_DESC ImageDesc;
		Image->GetLevelDesc(0, &ImageDesc);

		if (w && h)
		{
			setWidth(w);
			setHeight(h);
		}
		else
		{
			setWidth(ImageDesc.Width);
			setHeight(ImageDesc.Height);
		}

		trueWidth = ImageDesc.Width;
		trueHeight = ImageDesc.Height;
	}
}

void UIImageOld::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (isVisible())
	{

		if (iWidth <= 0 || iHeight <= 0)
			return;

		int cX = getX();
		int cY = getY();
		int cWidth = getWidth();
		int cHeight = getHeight();
		int wResizer = -1;
		int hResizer = -1;

		if (eDrawStyle == EDRAW_Adjust)
		{

			if (cWidth != trueWidth)
			{
				wResizer = cWidth;
				cWidth = trueWidth;
			}

			if (cHeight != trueHeight)
			{
				hResizer = cHeight;
				cHeight = trueHeight;
			}
		}

		int iStartX = cX < iSourceX ? abs(cX - iSourceX) : 0;
		int iStartY = cY < iSourceY ? abs(cY - iSourceY) : 0;
		int iRenderWidth = low(cWidth, iWidth);
		int iRenderHeight = low(cHeight, iHeight);
		int iRenderX = cX + iX + iStartX;
		int iRenderY = cY + iY + iStartY;

		if (wResizer == -1)
		{
			if (cX + iRenderWidth > iWidth)
				iRenderWidth -= (cX + iRenderWidth) - iWidth;
		}
		else
		{
			if (cX + wResizer > iWidth)
			{
				iRenderWidth -= (cX + wResizer) - iWidth;
				wResizer -= (cX + wResizer) - iWidth;
			}
		}

		if (hResizer == -1)
		{
			if (cY + iRenderHeight > iHeight)
				iRenderHeight -= (cY + iRenderHeight) - iHeight;
		}
		else
		{
			if (cY + hResizer > iHeight)
			{
				iRenderHeight -= (cY + hResizer) - iHeight;
				hResizer -= (cY + hResizer) - iHeight;
			}
		}

		if (Image && iStartX < iRenderWidth && iStartY < iRenderHeight)
		{
			DrawSprite(iRenderX, iRenderY, Image, iStartX + startX, iStartY + startY, iRenderWidth + startX, iRenderHeight + startY, 777, wResizer, hResizer);
		}
		if (isMousePos(iRenderX, iRenderY, iRenderWidth, iRenderHeight))
		{
			if (fHover)
				fHover();
		}
	}
}

void UIImageOld::SetImage(char* path)
{
	Image = LoadUIImage(path);

	if (Image)
	{
		D3DSURFACE_DESC ImageDesc;
		Image->GetLevelDesc(0, &ImageDesc);

		setWidth(ImageDesc.Width);
		setHeight(ImageDesc.Height);

		trueWidth = ImageDesc.Width;
		trueHeight = ImageDesc.Height;
	}
}
