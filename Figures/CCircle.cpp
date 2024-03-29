#include "CCircle.h"

#include "../Core/Application.h"

CCircle::CCircle(int figID, Point center, Point radiusPoint, GfxInfo gfxInfo) : CFigure(figID, gfxInfo)
{
	m_Center = center;
	m_RadiusPoint = radiusPoint;

	UpdateRadius();
}

CCircle::CCircle(GfxInfo gfxInfo) : CFigure(-1, gfxInfo)
{
	m_Center = m_RadiusPoint = Point();
	m_Radius = 0;
}

void CCircle::UpdateRadius()
{
	m_Radius = ((Vector2)m_Center - m_RadiusPoint).Magnitude();
}

void CCircle::GetNodes(FigureNode*** nodes, int* sz)
{
	if (nodes == 0) return;

	//circle has 1 node
	*sz = 1;

	*nodes = new FigureNode* [1] {
		&m_Node
	};
}

void CCircle::Draw(Output* pOut)
{
	Application* app = GetApplication();

	//push current gfx info to the stack
	app->PushGfxInfo(m_GfxInfo);

	//draw
	pOut->DrawCircle(m_Center, m_RadiusPoint, m_Selected);

	//pop gfx info
	app->PopGfxInfo();

	//render nodes
	if (m_ShouldRenderNodes) 
	{
		m_Node.SetPosition(m_RadiusPoint);
		m_Node.RenderNode(pOut);
	}
}

bool CCircle::HitTest(Point hit)
{
	//for a circle
	//distance between hit and center must be <= radius
	int distance = ((Vector2)hit - m_Center).Magnitude();
	return distance <= m_Radius;
}

void CCircle::PrintInfo(const UIFrontend* frontend) const
{
	char buf[100];
	sprintf(buf, "CIRCLE: ID(%d) Center(%d, %d) Radius(%d)", m_ID, m_Center.x, m_Center.y, m_Radius);

	frontend->SetStatusBarText(buf);
}

void CCircle::Translate(int dx, int dy)
{
	//circle, we translate the center and radius point, the radius itself remains constant
	m_Center.x += dx;
	m_Center.y += dy;

	m_RadiusPoint.x += dx;
	m_RadiusPoint.y += dy;
}

void CCircle::Resize(FigureNode* targetNode)
{
	//center is constant
	//radius point would keep moving
	m_RadiusPoint = m_Node.GetPosition();

	UpdateRadius();
}

Point CCircle::GetPosition()
{
	return m_Center;
}

DWShape CCircle::GetShape()
{
	return DWSHAPE_CIRCLE;
}

void CCircle::Save(Serializer* serializer)
{
	serializer->Write(GetShape());
	serializer->Write(m_ID);

	//coords
	serializer->WritePoint(m_Center);
	serializer->WritePoint(m_RadiusPoint);

	//gfx info
	serializer->WriteColor(m_GfxInfo.draw_col);
	serializer->WriteColor(m_GfxInfo.fill_col);
	serializer->Write(m_GfxInfo.is_filled);
}

void CCircle::Load(Deserializer* deserializer)
{
	//read id
	m_ID = deserializer->Read<int>();

	//read coords
	m_Center = deserializer->ReadPoint();
	m_RadiusPoint = deserializer->ReadPoint();

	//gfx info
	m_GfxInfo.draw_col = deserializer->ReadColor();
	m_GfxInfo.fill_col = deserializer->ReadColor();
	m_GfxInfo.is_filled = deserializer->Read<bool>();

	//further computations
	UpdateRadius();
}
