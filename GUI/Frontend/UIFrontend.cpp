#include "UIFrontend.h"
#include "UISprite.h"
#include "UILineRenderer.h"
#include "../UI_Info.h"

#define TOOLBAR_SPACING 15

UIFrontend::UIFrontend()
{
	//initialize display
	m_Display = new UIDisplay(Vector2(UI.width, UI.height));

	CreateToolBar();
	CreateStatusBar();
}

void UIFrontend::CreateToolBar()
{
	//render toolbar
	m_Toolbar = new UIWindow(m_Display, UIAnchor::None, Rect(0, 0, UI.width, UI.ToolBarHeight), Color(100, 100, 100, 255), false);

	//shapes textures
	std::string shapeTextures[DWSHAPE_COUNT];
	shapeTextures[DWSHAPE_RECTANGLE] = "images\\draw\\shapes\\img_rect.jpg";
	shapeTextures[DWSHAPE_SQUARE] = "images\\draw\\shapes\\img_square.jpg";
	shapeTextures[DWSHAPE_TRIANGLE] = "images\\draw\\shapes\\img_triangle.jpg";
	shapeTextures[DWSHAPE_HEXAGON] = "images\\draw\\shapes\\img_hexagon.jpg";
	shapeTextures[DWSHAPE_CIRCLE] = "images\\draw\\shapes\\img_circle.jpg";

	ActionType shapeActions[DWSHAPE_COUNT];
	for (ActionType type = ActionType(ACTION_DRAW_SHAPE_BEGIN + 1); type < ACTION_DRAW_SHAPE_END; type = ActionType(type + 1))
	{
		shapeActions[type - ACTION_DRAW_SHAPE_BEGIN - 1] = type;
	}

	//delta x position
	int dx = 0;

	//render shape list
	m_ShapeList = new UIButtonList(
		m_Toolbar,
		UIAnchor::None,
		Rect(dx, 0, UI.MenuItemWidth * DWSHAPE_COUNT, UI.ToolBarHeight),
		true,
		DWSHAPE_COUNT,
		shapeTextures,
		shapeActions);

	dx += m_ShapeList->ScreenRect().w + TOOLBAR_SPACING; //increment dx with shapelist's width + 5 px padding

	//render line below toolbar
	new UILineRenderer(m_Toolbar, UIAnchor::Bottom, Rect(0, -1, UI.width, 0), 3, Color(255, 0, 0, 255));

	//color palette
	std::string colorTextures[DWCOLOR_COUNT];
	colorTextures[DWCOLOR_BLACK] = "images\\draw\\colors\\img_black.jpg";
	colorTextures[DWCOLOR_YELLOW] = "images\\draw\\colors\\img_yellow.jpg";
	colorTextures[DWCOLOR_ORANGE] = "images\\draw\\colors\\img_orange.jpg";
	colorTextures[DWCOLOR_RED] = "images\\draw\\colors\\img_red.jpg";
	colorTextures[DWCOLOR_GREEN] = "images\\draw\\colors\\img_green.jpg";
	colorTextures[DWCOLOR_BLUE] = "images\\draw\\colors\\img_blue.jpg";

	ActionType colorActions[DWCOLOR_COUNT];
	for (ActionType type = ActionType(ACTION_DRAW_COL_BEGIN + 1); type < ACTION_DRAW_COL_END; type = ActionType(type + 1))
	{
		colorActions[type - ACTION_DRAW_COL_BEGIN - 1] = type;
	}

	//render color palette
	m_ColorPalette = new UIButtonList(m_Toolbar,
		UIAnchor::None,
		Rect(dx, 0, UI.MenuItemWidth * DWCOLOR_COUNT, UI.ToolBarHeight),
		true,
		DWCOLOR_COUNT,
		colorTextures,
		colorActions);

	dx += m_ColorPalette->ScreenRect().w + TOOLBAR_SPACING; //increment dx with color pallete's width + 5 px padding

	//color mode
	std::string colorModeTextures[DWCOLORMODE_COUNT];
	colorModeTextures[DWCOLORMODE_FILL] = "images\\draw\\other\\img_fill.jpg";
	colorModeTextures[DWCOLORMODE_DRAW] = "images\\draw\\other\\img_draw.jpg";

	ActionType colorModeActions[DWCOLORMODE_COUNT];
	for (ActionType type = ActionType(ACTION_DRAW_COLMODE_BEGIN + 1); type < ACTION_DRAW_COLMODE_END; type = ActionType(type + 1))
	{
		colorModeActions[type - ACTION_DRAW_COLMODE_BEGIN - 1] = type;
	}

	//render color palette
	m_ColorPrefList = new UIButtonList(m_Toolbar,
		UIAnchor::None,
		Rect(dx, 0, UI.MenuItemWidth * DWCOLORMODE_COUNT, UI.ToolBarHeight),
		true,
		DWCOLORMODE_COUNT,
		colorModeTextures,
		colorModeActions);

	dx += m_ColorPrefList->ScreenRect().w + TOOLBAR_SPACING;

	//other actions
	std::string otherTextures[DWOTHER_COUNT];
	otherTextures[DWOTHER_SELECT] = "images\\draw\\other\\img_select.jpg";
	otherTextures[DWOTHER_DELETE_FIG] = "images\\draw\\other\\img_delete_fig.jpg";
	otherTextures[DWOTHER_CLEAR_ALL] = "images\\draw\\other\\img_clear_all.jpg";
	otherTextures[DWOTHER_SAVE_GRAPH] = "images\\draw\\other\\img_save.jpg";
	otherTextures[DWOTHER_OPEN_GRAPH] = "images\\draw\\other\\img_open.jpg";
	otherTextures[DWOTHER_REC_START] = "images\\draw\\other\\img_rec_start.jpg";
	otherTextures[DWOTHER_REC_STOP] = "images\\draw\\other\\img_rec_stop.jpg";
	otherTextures[DWOTHER_REC_PAUSE] = "images\\draw\\other\\img_rec_pause.jpg";
	otherTextures[DWOTHER_UNDO] = "images\\draw\\other\\img_undo.jpg";
	otherTextures[DWOTHER_REDO] = "images\\draw\\other\\img_redo.jpg";
	otherTextures[DWOTHER_PLAY] = "images\\draw\\other\\img_play.jpg";
	otherTextures[DWOTHER_EXIT] = "images\\draw\\other\\img_exit.jpg";

	ActionType otherActions[DWOTHER_COUNT];
	for (ActionType type = ActionType(ACTION_DRAW_OTHER_BEGIN + 1); type < ACTION_DRAW_OTHER_END; type = ActionType(type + 1))
	{
		otherActions[type - ACTION_DRAW_OTHER_BEGIN - 1] = type;
	}

	//render other actions
	m_ColorPrefList = new UIButtonList(m_Toolbar,
		UIAnchor::None,
		Rect(dx, 0, UI.MenuItemWidth * DWOTHER_COUNT, UI.ToolBarHeight),
		false,
		DWOTHER_COUNT,
		otherTextures,
		otherActions);
}

void UIFrontend::CreateStatusBar()
{
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
