#include "CHexagon.h"
#include "../Core/Application.h"
#include "../Utils/GeoUtils.h"

CHexagon::CHexagon(int figID, Point center, GfxInfo gfxInfo) : CFigure(figID, gfxInfo)
{
	m_Center = center;
}

CHexagon::CHexagon(GfxInfo gfxInfo) : CFigure(-1, gfxInfo)
{
	m_Center = Point();
}

void CHexagon::GetNodes(FigureNode*** nodes, int* sz)
{
	if (nodes == 0) return;

	*sz = 1;

	*nodes = new FigureNode* [1] {
		&m_Node
	};
}

void CHexagon::Draw(Output* pOut)
{
	Application* app = GetApplication();

	//push current gfx info to the stack
	app->PushGfxInfo(m_GfxInfo);

	//draw
	pOut->DrawHexagon(m_Center, m_Selected);

	//pop gfx info
	app->PopGfxInfo();

	//render nodes
	if (m_ShouldRenderNodes)
	{
		//@ theta = 0
		//centerx + cosf(theta) * radius;
		//centery - sinf(theta) * radius;

		m_Node.SetPosition(Point{
			m_Center.x + m_GfxInfo.fixed_radius,
			m_Center.y
		});

		m_Node.RenderNode(pOut);
	}
}

bool CHexagon::HitTest(Point hit)
{
	int* x = 0;
	int* y = 0;
	GetSegmentedCirclePoints(m_Center, 6, m_GfxInfo.fixed_radius, &x, &y);

	//PointInPolygon takes a point array so create one
	Point points[6];
	for (int i = 0; i < 6; i++)
	{
		points[i] = Point{ x[i], y[i] };
	}

	//use point in polygon algorithm
	bool test = PointInPolygon(hit, points, 6);

	//cleanup
	delete[] x;
	delete[] y;

	return test;
}

void CHexagon::PrintInfo(const UIFrontend* frontend) const
{
	char buf[100];
	sprintf(buf, "HEXAGON: ID(%d) Center(%d, %d) Radius(%d)", m_ID, m_Center.x, m_Center.y, m_GfxInfo.fixed_radius);

	frontend->SetStatusBarText(buf);
}

void CHexagon::Translate(int dx, int dy)
{
	//hexagon, we translate the center
	m_Center.x += dx;
	m_Center.y += dy;
}

void CHexagon::Resize(FigureNode* targetNode)
{
	//radius is magnitude of vector between node pos and center
	Vector2 dir = (Vector2)m_Center - m_Node.GetPosition();

	m_GfxInfo.fixed_radius = dir.Magnitude();
}

Point CHexagon::GetPosition()
{
	return m_Center;
}

DWShape CHexagon::GetShape()
{
	return DWSHAPE_HEXAGON;
}

void CHexagon::Save(Serializer* serializer)
{
	serializer->Write(GetShape());
	serializer->Write(m_ID);

	//coords
	serializer->WritePoint(m_Center);

	//gfx info
	serializer->WriteColor(m_GfxInfo.draw_col);
	serializer->WriteColor(m_GfxInfo.fill_col);
	serializer->Write(m_GfxInfo.is_filled);
}

void CHexagon::Load(Deserializer* deserializer)
{
	//read id
	m_ID = deserializer->Read<int>();

	//read coords
	m_Center = deserializer->ReadPoint();

	//gfx info
	m_GfxInfo.draw_col = deserializer->ReadColor();
	m_GfxInfo.fill_col = deserializer->ReadColor();
	m_GfxInfo.is_filled = deserializer->Read<bool>();
}