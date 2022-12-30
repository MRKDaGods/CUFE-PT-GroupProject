#include "CSquare.h"

#include "../Core/Application.h"

CSquare::CSquare(Point center, GfxInfo gfxInfo) : CFigure(gfxInfo)
{
	m_Center = center;

	UpdateScreenSpaceRect();
}

CSquare::CSquare(GfxInfo gfxInfo) : CFigure(gfxInfo)
{
	m_Center = Point();
	m_Rect = Rect();
}

void CSquare::UpdateScreenSpaceRect()
{
	int xmin = m_Center.x - m_GfxInfo.fixed_radius;
	int ymin = m_Center.y - m_GfxInfo.fixed_radius;

	//a square has equal dimensions which are equal to 2 * radius
	int dim = 2 * m_GfxInfo.fixed_radius;

	m_Rect = Rect(xmin, ymin, dim, dim);
}

void CSquare::Draw(Output* pOut) const
{
	Application* app = GetApplication();

	//push current gfx info to the stack
	app->PushGfxInfo(m_GfxInfo);

	//draw
	pOut->DrawSquare(m_Center, m_Selected);

	//pop gfx info
	app->PopGfxInfo();
}

bool CSquare::HitTest(Point hit)
{
	//true if hit lies inside the screenspace rectangle
	return m_Rect.Contains(hit);
}

void CSquare::PrintInfo(const UIFrontend* frontend) const
{
	char buf[100];
	sprintf(buf, "SQUARE: ID(%d) START POINT(%d, %d) Width(%d) Height(%d)", m_ID, (int)m_Rect.x, (int)m_Rect.y, (int)m_Rect.w, (int)m_Rect.h);

	frontend->SetStatusBarText(buf);
}

void CSquare::Translate(int dx, int dy)
{
	//square, we translate the center
	m_Center.x += dx;
	m_Center.y += dy;

	//update after modification
	UpdateScreenSpaceRect();
}

Point CSquare::GetPosition()
{
	return m_Center;
}

void CSquare::Save(Serializer* serializer)
{
	serializer->Write(DWSHAPE_SQUARE);
	serializer->Write(m_ID);

	//coords
	serializer->WritePoint(m_Center);

	//gfx info
	serializer->WriteColor(m_GfxInfo.draw_col);
	serializer->WriteColor(m_GfxInfo.fill_col);
	serializer->Write(m_GfxInfo.is_filled);
}

void CSquare::Load(Deserializer* deserializer)
{
	//read id
	m_ID = deserializer->Read<int>();

	//read coords
	m_Center = deserializer->ReadPoint();

	//gfx info
	m_GfxInfo.draw_col = deserializer->ReadColor();
	m_GfxInfo.fill_col = deserializer->ReadColor();
	m_GfxInfo.is_filled = deserializer->Read<bool>();

	//further computations
	UpdateScreenSpaceRect();
}
