#include "CFigure.h"

CFigure::CFigure(GfxInfo gfxInfo)
{
	m_GfxInfo = gfxInfo;	//Default status is non-filled.
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

void CFigure::ChangeDrawColor(color Dclr)
{
	m_GfxInfo.draw_col = Dclr;
}

void CFigure::ChangeFillColor(color Fclr)
{
	m_GfxInfo.is_filled = true;
	m_GfxInfo.fill_col = Fclr;
}

