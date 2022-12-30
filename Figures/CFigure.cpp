#include "CFigure.h"
#include "../Utils/Color.h"

CFigure::CFigure(GfxInfo gfxInfo)
{
	m_ID = 0;
	m_GfxInfo = gfxInfo;
	m_Selected = false;
}

void CFigure::SetSelected(bool s)
{
	m_Selected = s;
}

bool CFigure::IsSelected() const
{
	return m_Selected;
}

GfxInfo* CFigure::GetGfxInfo()
{
	return &m_GfxInfo;
}

void CFigure::ChangeDrawColor(color Dclr)
{
	m_GfxInfo.draw_col = Dclr;
}

void CFigure::ChangeFillColor(color Fclr)
{
	m_GfxInfo.is_filled = true;
	m_GfxInfo.fill_col = Fclr;
}