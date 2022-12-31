#include "CRectangle.h"
#include "../Core/Application.h"

CRectangle::CRectangle(int figID, Point p1, Point p2, GfxInfo gfxInfo) : CFigure(figID, gfxInfo)
{
	m_P1 = p1;
	m_P2 = p2;

	//update our local rect
	UpdateScreenSpaceRect();
}

CRectangle::CRectangle(GfxInfo gfxInfo) : CFigure(-1, gfxInfo)
{
	m_P1 = m_P2 = Point();
	m_Rect = Rect();
}


void CRectangle::UpdateScreenSpaceRect()
{
	int xmin = min(m_P1.x, m_P2.x);
	int ymin = min(m_P1.y, m_P2.y);

	int xmax = max(m_P1.x, m_P2.x);
	int ymax = max(m_P1.y, m_P2.y);

	m_Rect = Rect(xmin, ymin, xmax - xmin, ymax - ymin);
}

void CRectangle::GetNodes(FigureNode*** nodes, int* sz)
{
	if (nodes == 0) return;

	*sz = 4;

	*nodes = new FigureNode* [4] {
		&(m_Nodes[0]), &(m_Nodes[1]), &(m_Nodes[2]), &(m_Nodes[3]),
	};
}

void CRectangle::Draw(Output* pOut)
{
	Application* app = GetApplication();

	//push current gfx info to the stack
	app->PushGfxInfo(m_GfxInfo);

	//draw
	pOut->DrawRectangle(m_P1, m_P2, m_Selected);

	//pop gfx info
	app->PopGfxInfo();

	//render nodes
	if (m_ShouldRenderNodes)
	{
		Point points[4] { 
			Point{ (int)m_Rect.XMin(), (int)m_Rect.YMin() },
			Point{ (int)m_Rect.XMax(), (int)m_Rect.YMin() },
			Point{ (int)m_Rect.XMin(), (int)m_Rect.YMax() },
			Point{ (int)m_Rect.XMax(), (int)m_Rect.YMax() }
		};

		for (int i = 0; i < 4; i++)
		{
			m_Nodes[i].SetPosition(points[i]);
			m_Nodes[i].RenderNode(pOut);
		}
	}
}

bool CRectangle::HitTest(Point hit)
{
	//true if hit lies inside the rectangle
	return m_Rect.Contains(hit);
}

void CRectangle::PrintInfo(const UIFrontend* frontend) const
{
	char buf[100];
	sprintf(buf, "RECTANGLE: ID(%d) START POINT(%d, %d) Width(%d) Height(%d)", m_ID, (int)m_Rect.x, (int)m_Rect.y, (int)m_Rect.w, (int)m_Rect.h);

	frontend->SetStatusBarText(buf);
}

void CRectangle::Translate(int dx, int dy)
{
	//rectangle, we translate p1 and p2
	m_P1.x += dx;
	m_P1.y += dy;

	m_P2.x += dx;
	m_P2.y += dy;

	//update after modification
	UpdateScreenSpaceRect();
}

void CRectangle::Resize(FigureNode* targetNode)
{
	int nodeIdx = -1;
	for (int i = 0; i < 4; i++)
	{
		if (&(m_Nodes[i]) == targetNode)
		{
			nodeIdx = i;
			break;
		}
	}

	int x1 = m_Rect.XMin();
	int y1 = m_Rect.YMin(); 
	int x2 = m_Rect.XMax(); 
	int y2 = m_Rect.YMax();

	Point nodePos = targetNode->GetPosition();

	switch (nodeIdx)
	{
	case 0:
		x1 = nodePos.x;
		y1 = nodePos.y;
		break;

	case 1:
		x2 = nodePos.x;
		y1 = nodePos.y;
		break;

	case 2:
		x1 = nodePos.x;
		y2 = nodePos.y;
		break;

	case 3:
		x2 = nodePos.x;
		y2 = nodePos.y;
		break;
	}

	//top left
	m_P1 = Point{ x1, y1 };

	//bottom right
	m_P2 = Point{ x2, y2 };

	//update rect
	UpdateScreenSpaceRect();
}

Point CRectangle::GetPosition()
{
	//return the center of the rectangle
	return Point{
		(int)((m_Rect.XMin() + m_Rect.XMax()) * 0.5f),
		(int)((m_Rect.YMin() + m_Rect.YMax()) * 0.5f)
	};
}

DWShape CRectangle::GetShape()
{
	return DWSHAPE_RECTANGLE;
}

void CRectangle::Save(Serializer* serializer)
{
	serializer->Write(GetShape());
	serializer->Write(m_ID);

	//coords
	serializer->WritePoint(m_P1);
	serializer->WritePoint(m_P2);

	//gfx info
	serializer->WriteColor(m_GfxInfo.draw_col);
	serializer->WriteColor(m_GfxInfo.fill_col);
	serializer->Write(m_GfxInfo.is_filled);
}

void CRectangle::Load(Deserializer* deserializer)
{
	//read id
	m_ID = deserializer->Read<int>();

	//read coords
	m_P1 = deserializer->ReadPoint();
	m_P2 = deserializer->ReadPoint();

	//gfx info
	m_GfxInfo.draw_col = deserializer->ReadColor();
	m_GfxInfo.fill_col = deserializer->ReadColor();
	m_GfxInfo.is_filled = deserializer->Read<bool>();

	//further computations
	UpdateScreenSpaceRect();
}
