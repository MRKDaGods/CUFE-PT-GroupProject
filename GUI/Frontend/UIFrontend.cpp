#include "UIFrontend.h"
#include "UISprite.h"
#include "UILineRenderer.h"
#include "../UI_Info.h"

UIFrontend::UIFrontend()
{
	//initialize display
	m_Display = new UIDisplay(Vector2(UI.width, UI.height));

	//render toolbar
	m_Toolbar = new UIWindow(m_Display, UIAnchor::None, Rect(0, 0, UI.width, UI.ToolBarHeight), Color(255, 255, 255, 255), false);

	//shapes textures
	std::string shapeTextures[5];
	shapeTextures[SHAPE_RECTANGLE - 1] = "images\\draw\\shapes\\img_rect.jpg";
	shapeTextures[SHAPE_SQUARE - 1] = "images\\draw\\shapes\\img_square.jpg";
	shapeTextures[SHAPE_TRIANGLE - 1] = "images\\draw\\shapes\\img_triangle.jpg";
	shapeTextures[SHAPE_HEXAGON - 1] = "images\\draw\\shapes\\img_hexagon.jpg";
	shapeTextures[SHAPE_CIRCLE - 1] = "images\\draw\\shapes\\img_circle.jpg";

	//render shape list
	m_ShapeList = new UIShapeList(m_Toolbar, UIAnchor::None, Rect(0, 0, UI.MenuItemWidth * 5, UI.ToolBarHeight), shapeTextures);

	//render line below toolbar
	new UILineRenderer(m_Toolbar, UIAnchor::Bottom, Rect(0, -1, UI.width, 0), 3, Color(255, 0, 0, 255));

	//render status bar
	color c = UI.StatusBarColor;
	m_StatusBar = new UIWindow(m_Display, UIAnchor::Bottom, Rect(0, UI.StatusBarHeight, UI.width, UI.StatusBarHeight), Color(c.ucRed, c.ucGreen, c.ucBlue, 255), false);

	m_StatusBarLabel = new UILabel(m_StatusBar, UIAnchor::BottomLeft, Rect(10, UI.StatusBarHeight, UI.width - 10, UI.StatusBarHeight), 20, "");
}

UIFrontend::~UIFrontend()
{
	delete m_Display;
}

void UIFrontend::Render()
{
	m_Display->Draw();
}

void UIFrontend::SetStatusBarText(string txt)
{
	m_StatusBarLabel->SetText(txt);
}

void UIFrontend::HandleTouchEvent(UITouchEvent* evt)
{
	m_Display->HandleTouchEvent(evt);
}
