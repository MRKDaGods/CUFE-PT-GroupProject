#include "CSquare.h"

#include "../Core/Application.h"

CSquare::CSquare(Point center, GfxInfo gfxInfo) : CFigure(gfxInfo)
{
	m_Center = center;
}


void CSquare::Draw(Output* pOut) const
{
	Application* app = GetApplication();

	//push current gfx info to the stack
	app->PushGfxInfo(m_GfxInfo);

	//draw
	pOut->DrawSquare(m_Center, m_Selected);

	//pop gfx info
	app->PopGfxInfo();
}