#include "CRectangle.h"

#include "../Core/Application.h"

CRectangle::CRectangle(Point p1, Point p2, GfxInfo gfxInfo) : CFigure(gfxInfo)
{
	m_P1 = p1;
	m_P2 = p2;
}


void CRectangle::Draw(Output* pOut) const
{
	Application* app = GetApplication();

	//push current gfx info to the stack
	app->PushGfxInfo(m_GfxInfo);

	//draw
	pOut->DrawRectangle(m_P1, m_P2, m_Selected);

	//pop gfx info
	app->PopGfxInfo();
}