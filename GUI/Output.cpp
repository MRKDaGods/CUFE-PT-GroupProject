#include "Output.h"
#include "../Core/Application.h"

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

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	//CreateDrawToolBar();
	//CreateStatusBar();
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
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[DRAW_ITM_RECT] = "images\\draw\\shapes\\img_rect.jpg";
	MenuItemImages[DRAW_ITM_SQUARE] = "images\\draw\\shapes\\img_square.jpg";
	MenuItemImages[DRAW_ITM_TRIANGLE] = "images\\draw\\shapes\\img_triangle.jpg";
	MenuItemImages[DRAW_ITM_HEXAGON] = "images\\draw\\shapes\\img_hexagon.jpg";
	MenuItemImages[DRAW_ITM_CIRCLE] = "images\\draw\\shapes\\img_circle.jpg";
	MenuItemImages[DRAW_ITM_SELECT] = "images\\draw\\other\\img_select.jpg";

	MenuItemImages[DRAW_ITM_COL_BLACK] = "images\\draw\\colors\\img_black.jpg";
	MenuItemImages[DRAW_ITM_COL_YELLOW] = "images\\draw\\colors\\img_yellow.jpg";
	MenuItemImages[DRAW_ITM_COL_ORANGE] = "images\\draw\\colors\\img_orange.jpg";
	MenuItemImages[DRAW_ITM_COL_RED] = "images\\draw\\colors\\img_red.jpg";
	MenuItemImages[DRAW_ITM_COL_GREEN] = "images\\draw\\colors\\img_green.jpg";
	MenuItemImages[DRAW_ITM_COL_BLUE] = "images\\draw\\colors\\img_blue.jpg";

	//draw toolbar icons
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
	{
		int x = i * (UI.MenuItemWidth + UI.IconSeperatorWidth) + UI.IconPadding.left; // seperatorwidth for padding purposes and to draw the line seperator
		pWind->DrawImage(MenuItemImages[i],
			x,
			UI.IconPadding.top,
			UI.MenuItemWidth - UI.IconPadding.right - UI.IconPadding.left,
			UI.ToolBarHeight - UI.IconPadding.bottom - UI.IconPadding.top);

		//draw a black line after icon
		pWind->SetPen(BLACK, UI.IconSeperatorWidth);
		pWind->DrawLine(x + UI.MenuItemWidth, 0, x + UI.MenuItemWidth, UI.ToolBarHeight);
	}

	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight + 1, UI.width, UI.ToolBarHeight + 1); // +1 to account for the extra pixel rendered (line width = 3)

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	///TODO: write code to create Play mode menu
}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
	
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

	//draw it as a circle with 6 segments
	float _2pi = 2 * M_PI;
	float adv = _2pi / 6.0f;

	int x[6];
	int y[6];

	int idx = 0;
	for (float theta = adv; theta < _2pi; theta += adv)
	{
		x[idx] = center.x + cosf(theta) * gfxInfo->fixed_radius;
		y[idx] = center.y - sinf(theta) * gfxInfo->fixed_radius;
		idx++;
	}

	pWind->DrawPolygon(x, y, 6, style);
}

void Output::DrawCircle(Point center, Point radiusPoint, bool selected) const
{
	//prepare figure and get drawstyle
	drawstyle style = PrepareFigureRendering(selected);

	//calculate distance between the 2 points
	int radius = (int)sqrtf(powf(center.x - radiusPoint.x, 2.0f) + powf(center.y - radiusPoint.y, 2.0f));
	pWind->DrawCircle(center.x, center.y, radius, style);
}


//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

