#include "CRectangle.h"

CRectangle::CRectangle(Point p1, Point p2, GfxInfo gfxInfo) : CFigure(gfxInfo)
{
	m_P1 = p1;
	m_P2 = p2;
}


void CRectangle::Draw(Output* pOut) const
{
	pOut->DrawRectangle(m_P1, m_P2, m_Selected);
}