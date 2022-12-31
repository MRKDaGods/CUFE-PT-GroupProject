#include "UIFrontend.h"
#include "UISprite.h"
#include "UILineRenderer.h"
#include "../UI_Info.h"
#include "../../Core/Application.h"

#define TOOLBAR_SPACING 15

UIFrontend::UIFrontend()
{
	//initialize display
	m_Display = new UIDisplay(Vector2(UI.width, UI.height));

	//instantiate components
	CreateToolBar();
	CreateStatusBar();

	//instantiate other elements
	CreateOtherElements();
}

void UIFrontend::CreateToolBar()
{
	//render toolbar
	m_Toolbar = new UIWindow(
		m_Display,
		UIAnchor::None,
		Rect(0, 0, UI.width, UI.ToolBarHeight),
		Color(100, 100, 100, 255),
		false,
		[]() {
			GetApplication()->GetOutput()->PrintMessage("Clicked on Empty Area on ToolBar");
		});

	//build draw mode toolbar
	BuildDrawModeToolBar();

	//build play mode toolbar
	BuildPlayModeToolBar();

	//create drawing area
	/*m_DrawingArea = new UIWindow(
		m_Display,
		UIAnchor::None,
		Rect(0, UI.ToolBarHeight + 3, UI.width, UI.height - UI.ToolBarHeight - UI.StatusBarHeight - 3),
		Color(UI.BkGrndColor.ucRed, UI.BkGrndColor.ucGreen, UI.BkGrndColor.ucBlue, 255),
		false,
		[]() {
			GetApplication()->GetOutput()->PrintMessage("Clicked on Drawing Area");
		});*/

	//render line below toolbar
	new UILineRenderer(m_Toolbar, UIAnchor::Bottom, Rect(0, -1, UI.width, 0), 3, Color(255, 0, 0, 255));

	//set to draw mode by default
	SetCurrentMode(false, false);
}

void UIFrontend::CreateStatusBar()
{
	//render status bar
	color c = UI.StatusBarColor;
	m_StatusBar = new UIWindow(
		m_Display,
		UIAnchor::Bottom,
		Rect(0, UI.StatusBarHeight, UI.width, UI.StatusBarHeight),
		Color(c.ucRed, c.ucGreen, c.ucBlue, 255),
		false,
		[]() {
			GetApplication()->GetOutput()->PrintMessage("Clicked on StatusBar");
		});

	m_StatusBarLabel = new UILabel(
		m_StatusBar,
		UIAnchor::BottomLeft,
		Rect(10, UI.StatusBarHeight, UI.width - 10, UI.StatusBarHeight),
		20,
		"");
}

void UIFrontend::CreateOtherElements()
{
	//recording label
	m_RecordingLabel = new UILabel(
		m_Display,
		UIAnchor::BottomRight,
		Rect(105, UI.StatusBarHeight + 40, 105, 40),
		24,
		"REC"
	);

	//initially false
	SetRecording(false);
}

void UIFrontend::BuildDrawModeToolBar()
{
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
		false,
		DWSHAPE_COUNT,
		shapeTextures,
		shapeActions,
		Color(255, 0, 0, 255));

	dx += m_ShapeList->ScreenRect().w + TOOLBAR_SPACING; //increment dx with shapelist's width + 5 px padding

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
		colorActions,
		Color(255, 255, 255, 255));

	//set black initially selected
	m_ColorPalette->UpdateSelectedButton(0, false);

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
		colorModeActions,
		Color(255, 0, 0, 255));

	//set draw initially selected
	m_ColorPrefList->UpdateSelectedButton(1, false);

	dx += m_ColorPrefList->ScreenRect().w + TOOLBAR_SPACING;

	//other actions
	std::string otherTextures[DWOTHER_COUNT];
	otherTextures[DWOTHER_SELECT] = "images\\draw\\other\\img_select.jpg";
	otherTextures[DWOTHER_MOVE] = "images\\draw\\other\\img_move.jpg";
	otherTextures[DWOTHER_DELETE_FIG] = "images\\draw\\other\\img_delete_fig.jpg";
	otherTextures[DWOTHER_CLEAR_ALL] = "images\\draw\\other\\img_clear_all.jpg";
	otherTextures[DWOTHER_SAVE_GRAPH] = "images\\draw\\other\\img_save.jpg";
	otherTextures[DWOTHER_OPEN_GRAPH] = "images\\draw\\other\\img_open.jpg";
	otherTextures[DWOTHER_REC_START] = "images\\draw\\other\\img_rec_start.jpg";
	otherTextures[DWOTHER_REC_STOP] = "images\\draw\\other\\img_rec_stop.jpg";
	otherTextures[DWOTHER_REC_PLAY] = "images\\draw\\other\\img_rec_pause.jpg";
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
	m_OtherActionsList = new UIButtonList(m_Toolbar,
		UIAnchor::None,
		Rect(dx, 0, UI.MenuItemWidth * DWOTHER_COUNT, UI.ToolBarHeight),
		false,
		DWOTHER_COUNT,
		otherTextures,
		otherActions,
		Color(255, 0, 0, 255));

	//left widgets
	m_DWLeftWidgetsContainer = new UIWindow(
		m_Display,
		UIAnchor::None,
		Rect(0, UI.ToolBarHeight + 3, UI.DrawAreaStartOffset, UI.height - UI.ToolBarHeight - UI.StatusBarHeight - 3),
		Color(UI.BkGrndColor.ucRed, UI.BkGrndColor.ucGreen, UI.BkGrndColor.ucBlue, 255)
	);

	//create the 3 buttons
	
	int dy = 0;

	//sound button
	new UIImageButton(
		m_DWLeftWidgetsContainer,
		UIAnchor::None,
		Rect(0, 0, UI.MenuItemWidth, UI.ToolBarHeight),
		"images\\draw\\other\\img_sound_off.jpg",
		Color(255, 255, 255, 255)
	);

	dy += UI.ToolBarHeight;

	new UIImageButton(
		m_DWLeftWidgetsContainer,
		UIAnchor::None,
		Rect(0, dy, UI.MenuItemWidth, UI.ToolBarHeight),
		"images\\draw\\other\\img_drag.jpg",
		Color(255, 255, 255, 255)
	);

	dy += UI.ToolBarHeight;

	new UIImageButton(
		m_DWLeftWidgetsContainer,
		UIAnchor::None,
		Rect(0, dy, UI.MenuItemWidth, UI.ToolBarHeight),
		"images\\draw\\other\\img_resize.jpg",
		Color(255, 255, 255, 255)
	);
}

void UIFrontend::BuildPlayModeToolBar()
{
	//pick hide textures
	std::string phTextures[PMPICKHIDE_COUNT];
	phTextures[PMPICKHIDE_FIG_TYPE] = "images\\play\\img_figtype.jpg";
	phTextures[PMPICKHIDE_FIG_COL] = "images\\play\\img_figcol.jpg";
	phTextures[PMPICKHIDE_FIG_TYPE_COL] = "images\\play\\img_figtypecol.jpg";

	ActionType phActions[PMPICKHIDE_COUNT];
	for (ActionType type = ActionType(ACTION_PLAY_PICKHIDE_BEGIN + 1); type < ACTION_PLAY_PICKHIDE_END; type = ActionType(type + 1))
	{
		phActions[type - ACTION_PLAY_PICKHIDE_BEGIN - 1] = type;
	}

	//delta x position
	int dx = 0;

	//render shape list
	m_PickHideList = new UIButtonList(
		m_Toolbar,
		UIAnchor::None,
		Rect(dx, 0, UI.MenuItemWidth * PMPICKHIDE_COUNT, UI.ToolBarHeight),
		true,
		PMPICKHIDE_COUNT,
		phTextures,
		phActions,
		Color(0, 0, 255, 255));

	dx += m_PickHideList->ScreenRect().w + TOOLBAR_SPACING;

	//other textures
	std::string otherTextures[PMOTHER_COUNT];
	otherTextures[PMOTHER_DRAW] = "images\\play\\img_draw.jpg";

	ActionType otherActions[PMOTHER_COUNT];
	for (ActionType type = ActionType(ACTION_PLAY_OTHER_BEGIN + 1); type < ACTION_PLAY_OTHER_END; type = ActionType(type + 1))
	{
		otherActions[type - ACTION_PLAY_OTHER_BEGIN - 1] = type;
	}

	m_PlayOtherList = new UIButtonList(
		m_Toolbar,
		UIAnchor::None,
		Rect(dx, 0, UI.MenuItemWidth * PMPICKHIDE_COUNT, UI.ToolBarHeight),
		false,
		PMOTHER_COUNT,
		otherTextures,
		otherActions,
		Color(0, 0, 255, 255));
}

void UIFrontend::SetDrawModeState(bool enable)
{
	m_ShapeList->SetVisible(enable, false);
	m_ColorPalette->SetVisible(enable, false);
	m_ColorPrefList->SetVisible(enable, false);
	m_OtherActionsList->SetVisible(enable, false);
	m_DWLeftWidgetsContainer->SetVisible(enable, false);
}

void UIFrontend::SetPlayModeState(bool enable)
{
	m_PickHideList->SetVisible(enable, false);
	m_PlayOtherList->SetVisible(enable, false);
}

UIFrontend::~UIFrontend()
{
	delete m_Display;
}

void UIFrontend::Render()
{
	m_Display->Draw();
}

void UIFrontend::SetStatusBarText(string txt) const
{
	m_StatusBarLabel->SetText(txt);
}

void UIFrontend::HandleTouchEvent(UITouchEvent* evt)
{
	m_Display->HandleTouchEvent(evt);
}

void UIFrontend::SetCurrentMode(bool isPlayMode, bool notify)
{
	//update mode states
	SetDrawModeState(!isPlayMode);
	SetPlayModeState(isPlayMode);

	//redraw
	if (notify)
	{
		m_Display->Draw();
	}
}

void UIFrontend::Reset()
{
	//reset to initial state
	m_ColorPalette->UpdateSelectedButton(DWCOLOR_BLACK, false);
	m_ColorPrefList->UpdateSelectedButton(DWCOLORMODE_DRAW, false);

	//TODO: play mode buttons?
}

void UIFrontend::SetSelectedColor(DWColors color)
{
	m_ColorPalette->UpdateSelectedButton(color);
}

void UIFrontend::SetSelectedColorMode(DWColorModes mode)
{
	m_ColorPrefList->UpdateSelectedButton(mode);
}

void UIFrontend::SetRecording(bool recording, bool invokeDirty, std::string text)
{
	//update rec label vis state
	m_RecordingLabel->SetVisible(recording, invokeDirty);

	if (recording)
	{
		//change text but dont notify, we will re-render on our own
		m_RecordingLabel->SetText(text, false);
	}
}
