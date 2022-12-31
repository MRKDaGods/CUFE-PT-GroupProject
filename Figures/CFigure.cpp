#include "CFigure.h"
#include "../Utils/Color.h"

CFigure::CFigure(int figID, GfxInfo gfxInfo)
{
	m_ID = figID;
	m_GfxInfo = gfxInfo;
	m_Selected = false;

	m_ShouldRenderNodes = false;
}

int CFigure::GetID()
{
	return m_ID;
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

void CFigure::SetNodeRenderingState(bool render)
{
	m_ShouldRenderNodes = render;
}

FigureNode* CFigure::GetNode(Point p)
{
	FigureNode** nodes = 0;
	int sz = 0;

	//get the nodes
	GetNodes(&nodes, &sz);

	//check if one of them satisfies p
	FigureNode* node = 0;
	for (int i = 0; i < sz; i++)
	{
		if (nodes[i]->HitTest(p))
		{
			//node found
			node = nodes[i];
			break;
		}
	}

	//clean up
	delete[] nodes;

	return node;
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