#include "FigureNode.h"
#include "../GUI/Output.h"

#define NODE_SZ 8

Rect FigureNode::GetRect()
{
	int halfSz = NODE_SZ / 2;
	return Rect(m_Pos.x - halfSz, m_Pos.y - halfSz, NODE_SZ, NODE_SZ);
}

FigureNode::FigureNode()
{
	m_Pos = Point();
}

void FigureNode::SetPosition(Point p)
{
	m_Pos = p;
}

Point FigureNode::GetPosition()
{
	return m_Pos;
}

bool FigureNode::HitTest(Point p)
{
	return GetRect().Contains(p);
}

void FigureNode::RenderNode(Output* output)
{
	//draw rect
	output->DrawRect(GetRect(), Color(255, 0, 0, 255));
}
