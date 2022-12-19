
#include "UIElement.h"
#include "DXGraphicEngine.h"
#include "Utils/Geometry.h"

// GODFATHER
BOOL bUIDebug = FALSE;

Element::Element()
{
}

Element::Element(Rectangle2D rRectangle) : rRect(rRectangle)
{
}

Element::~Element()
{
}

void Element::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
{
	if (bUIDebug)
	{
		GRAPHICENGINE->DrawRectangle2D(Rectangle2D(iX, iY, iWidth, 1), -1);
		GRAPHICENGINE->DrawRectangle2D(Rectangle2D(iX, iY + iHeight - 1, iWidth, 1), -1);
		GRAPHICENGINE->DrawRectangle2D(Rectangle2D(iX, iY, 1, iHeight), -1);
		GRAPHICENGINE->DrawRectangle2D(Rectangle2D(iX + iWidth - 1, iY, 1, iHeight), -1);
	}
}
