#include "CRectangle.h"
#include "../Core/Application.h"

CRectangle::CRectangle(Point p1, Point p2, GfxInfo gfxInfo) : CFigure(gfxInfo)
{
	m_P1 = p1;
	m_P2 = p2;

	//update our local rect
	UpdateScreenSpaceRect();
}

CRectangle::CRectangle(GfxInfo gfxInfo) : CFigure(gfxInfo)
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

Point CRectangle::GetPosition()
{
	//return the center of the rectangle
	return Point{
		(int)((m_Rect.XMin() + m_Rect.XMax()) * 0.5f),
		(int)((m_Rect.YMin() + m_Rect.YMax()) * 0.5f)
	};
}

void CRectangle::Save(Serializer* serializer)
{
	serializer->Write(DWSHAPE_RECTANGLE);
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
