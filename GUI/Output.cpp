#include "Output.h"
#include "../Core/Application.h"
#include "../Utils/GeoUtils.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define DEFINE_GFX_INFO GfxInfo* const gfxInfo = GetGfxInfo()

GfxInfo* Output::GetGfxInfo() const
{
	return ((Application*)m_App)->GetGfxInfo();
}

drawstyle Output::PrepareFigureRendering(bool selected, GfxInfo** callerGfx) const
{
	DEFINE_GFX_INFO;

	//set the gfx info of the caller incase needed
	if (callerGfx != 0)
	{
		*callerGfx = gfxInfo;
	}

	//set draw color
	color drawCol = selected ? UI.HighlightColor : gfxInfo->draw_col;
	pWind->SetPen(drawCol, 1);

	if (gfxInfo->is_filled)
	{
		pWind->SetBrush(gfxInfo->fill_col);
		return FILLED;
	}

	return FRAME;
}

Output::Output(void* app)
{
	//set app
	m_App = app;

	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1775;
	UI.height = 700;
	UI.wx = 5;
	UI.wy = 5;


	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 65;

	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames

	//padding
	UI.IconPadding = {
		0,0,0,0
	};

	//seperator width
	UI.IconSeperatorWidth = 1;

	//the draw area start offset to leave space for extra frontend UI elements
	UI.DrawAreaStartOffset = UI.MenuItemWidth; // 80;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{ 
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);	
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight + 3, UI.width, UI.height - UI.StatusBarHeight); //ammar: adjusted iY1 because of the toolbar line seperator
}

/////////////////////////////////////////////////////////////////////////////////////////
// ---   CUSTOM INTERFACE   ---
/////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearArea(Rect rect) const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(rect.x, rect.y, rect.w, rect.h);
}

void Output::DrawImage(Rect rect, string path)
{
	pWind->DrawImage(path, rect.x, rect.y, rect.w, rect.h);
}

void Output::DrawRect(Rect rect, Color c, bool filled, int width)
{
	color col = color(c.r * 255, c.g * 255, c.b * 255);
	pWind->SetPen(col, width);
	pWind->SetBrush(col);
	pWind->DrawRectangle(rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, filled ? FILLED : FRAME);
}

void Output::DrawLine(Vector2 p1, Vector2 p2, int w, Color c)
{
	color col = color(c.r * 255, c.g * 255, c.b * 255);
	pWind->SetPen(col, w);
	pWind->DrawLine(p1.x, p1.y, p2.x, p2.y);
}

void Output::DrawString(Rect rect, string msg, int fontSz)
{
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(fontSz, BOLD, BY_NAME, "Arial");
	pWind->DrawString(rect.x, rect.y, msg);
}

//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	int fontSz = 20;
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(fontSz, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, UI.height - UI.StatusBarHeight + fontSz * 0.5f, msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{	return UI.DrawColor;	}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{	return UI.FillColor;	}
//////////////////////////////////////////////////////////////////////////////////////////
	
int Output::getCrntPenWidth() const		//get current pen width
{	return UI.PenWidth;	}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRectangle(Point topLeft, Point botRight, bool selected) const
{
	//prepare figure and get drawstyle
	drawstyle style = PrepareFigureRendering(selected);
	
	pWind->DrawRectangle(topLeft.x, topLeft.y, botRight.x, botRight.y, style);
}

void Output::DrawSquare(Point center, bool selected) const
{
	//prepare figure and get drawstyle
	GfxInfo* gfxInfo;
	drawstyle style = PrepareFigureRendering(selected, &gfxInfo);

	//get corner points
	Point topLeft{ center.x - gfxInfo->fixed_radius, center.y - gfxInfo->fixed_radius };
	Point topRight{ center.x + gfxInfo->fixed_radius, center.y - gfxInfo->fixed_radius };
	Point botLeft{ center.x - gfxInfo->fixed_radius, center.y + gfxInfo->fixed_radius };
	Point botRight{ center.x + gfxInfo->fixed_radius, center.y + gfxInfo->fixed_radius };

	int x[4] = { topLeft.x, topRight.x, botRight.x, botLeft.x };
	int y[4] = { topLeft.y, topRight.y, botRight.y, botLeft.y };
	pWind->DrawPolygon(x, y, 4, style);
}

void Output::DrawTriangle(Point v1, Point v2, Point v3, bool selected) const
{
	//prepare figure and get drawstyle
	drawstyle style = PrepareFigureRendering(selected);

	int x[3] = { v1.x, v2.x, v3.x };
	int y[3] = { v1.y, v2.y, v3.y };
	pWind->DrawPolygon(x, y, 3, style);
}

void Output::DrawHexagon(Point center, bool selected) const
{
	//prepare figure and get drawstyle
	GfxInfo* gfxInfo;
	drawstyle style = PrepareFigureRendering(selected, &gfxInfo);

	int* x = 0;
	int* y = 0;
	GetSegmentedCirclePoints(center, 6, gfxInfo->fixed_radius, &x, &y);

	pWind->DrawPolygon(x, y, 6, style);

	delete[] x;
	delete[] y;
}

void Output::DrawCircle(Point center, Point radiusPoint, bool selected, int* outRadius) const
{
	//prepare figure and get drawstyle
	drawstyle style = PrepareFigureRendering(selected);

	//calculate distance between the 2 points
	int radius = ((Vector2)center - radiusPoint).Magnitude();

	if (outRadius) *outRadius = radius;

	pWind->DrawCircle(center.x, center.y, radius, style);
}


//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

