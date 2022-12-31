#include "CTriangle.h"
#include "../Core/Application.h"
#include "../Utils/GeoUtils.h"

#include <sstream>

CTriangle::CTriangle(int figID, Point p1, Point p2, Point p3, GfxInfo gfxInfo) : CFigure(figID, gfxInfo)
{
	m_P1 = p1;
	m_P2 = p2;
	m_P3 = p3;
}

CTriangle::CTriangle(GfxInfo gfxInfo) : CFigure(-1, gfxInfo)
{
	m_P1 = m_P2 = m_P3 = Point();
}

void CTriangle::GetNodes(FigureNode*** nodes, int* sz)
{
	if (nodes == 0) return;

	*sz = 3;

	*nodes = new FigureNode* [3] {
		&(m_Nodes[0]), & (m_Nodes[1]), & (m_Nodes[2])
	};
}

void CTriangle::Draw(Output* pOut)
{
	Application* app = GetApplication();

	//push current gfx info to the stack
	app->PushGfxInfo(m_GfxInfo);

	//draw
	pOut->DrawTriangle(m_P1, m_P2, m_P3, m_Selected);

	//pop gfx info
	app->PopGfxInfo();

	//render nodes
	if (m_ShouldRenderNodes)
	{
		Point points[3] {
			m_P1, m_P2, m_P3
		};

		for (int i = 0; i < 3; i++)
		{
			m_Nodes[i].SetPosition(points[i]);
			m_Nodes[i].RenderNode(pOut);
		}
	}
}

bool CTriangle::HitTest(Point hit)
{
	Point points[3] {
		m_P1, m_P2, m_P3
	};

	//use point in polygon algorithm
	return PointInPolygon(hit, points, 3);
}

void CTriangle::PrintInfo(const UIFrontend* frontend) const
{
	char buf[100];
	sprintf(buf, "TRIANGLE: ID(%d) V1(%d, %d) V2(%d, %d) V3(%d, %d)", m_ID, m_P1.x, m_P1.y, m_P2.x, m_P2.y, m_P3.x, m_P3.y);

	frontend->SetStatusBarText(buf);
}

void CTriangle::Translate(int dx, int dy)
{
	//triangle, we translate p1, p2 and p3
	m_P1.x += dx;
	m_P1.y += dy;

	m_P2.x += dx;
	m_P2.y += dy;

	m_P3.x += dx;
	m_P3.y += dy;
}

void CTriangle::Resize(FigureNode* targetNode)
{
	m_P1 = m_Nodes[0].GetPosition();
	m_P2 = m_Nodes[1].GetPosition();
	m_P3 = m_Nodes[2].GetPosition();
}

Point CTriangle::GetPosition()
{
	//centroid of triangle
	return Point{
		(m_P1.x + m_P2.x + m_P3.x) / 3,
		(m_P1.y + m_P2.y + m_P3.y) / 3
	};
}

DWShape CTriangle::GetShape()
{
	return DWSHAPE_TRIANGLE;
}

void CTriangle::Save(Serializer* serializer)
{
	serializer->Write(GetShape());
	serializer->Write(m_ID);

	//coords
	serializer->WritePoint(m_P1);
	serializer->WritePoint(m_P2);
	serializer->WritePoint(m_P3);

	//gfx info
	serializer->WriteColor(m_GfxInfo.draw_col);
	serializer->WriteColor(m_GfxInfo.fill_col);
	serializer->Write(m_GfxInfo.is_filled);
}

void CTriangle::Load(Deserializer* deserializer)
{
	//read id
	m_ID = deserializer->Read<int>();

	//read coords
	m_P1 = deserializer->ReadPoint();
	m_P2 = deserializer->ReadPoint();
	m_P3 = deserializer->ReadPoint();

	//gfx info
	m_GfxInfo.draw_col = deserializer->ReadColor();
	m_GfxInfo.fill_col = deserializer->ReadColor();
	m_GfxInfo.is_filled = deserializer->Read<bool>();
}