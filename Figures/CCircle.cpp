#include "CCircle.h"

#include "../Core/Application.h"

CCircle::CCircle(Point center, Point radiusPoint, GfxInfo gfxInfo) : CFigure(gfxInfo)
{
	m_Center = center;
	m_RadiusPoint = radiusPoint;

	m_Radius = ((Vector2)m_Center - m_RadiusPoint).Magnitude();
}

CCircle::CCircle(GfxInfo gfxInfo) : CFigure(gfxInfo)
{
	m_Center = m_RadiusPoint = Point();
	m_Radius = 0;
}


void CCircle::Draw(Output* pOut) const
{
	Application* app = GetApplication();

	//push current gfx info to the stack
	app->PushGfxInfo(m_GfxInfo);

	//draw
	pOut->DrawCircle(m_Center, m_RadiusPoint, m_Selected);

	//pop gfx info
	app->PopGfxInfo();
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

Point CCircle::GetPosition()
{
	return m_Center;
}

void CCircle::Save(Serializer* serializer)
{
	serializer->Write(DWSHAPE_CIRCLE);
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
	m_Radius = ((Vector2)m_Center - m_RadiusPoint).Magnitude();
}
