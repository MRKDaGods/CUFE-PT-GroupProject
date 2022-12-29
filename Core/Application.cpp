#include "Application.h"

#include "Actions/Shapes/ActionAddRectangle.h"
#include "Actions/Shapes/ActionAddSquare.h"
#include "Actions/Other/ActionExit.h"
#include "Actions/Colors/ActionSetColor.h"

#include <map>
#include <iostream>
#include <sstream>

//Action function pointer
#define _ACT_FNPTR(actClass) [](Application* app) -> Action* { return new actClass(app); }
#define _ACT_FNPTR_COL(col) [](Application* app) -> Action* { return new ActionSetColor(app, col); }

//ActionType to function pointer that returns a new instance of the action
std::map<ActionType, ActionInstantiator> actionDataTable2 {
	//////////////////////////////////////////////
	//Shape actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_SHAPE_RECTANGLE, _ACT_FNPTR(ActionAddRectangle) },
	{ ACTION_DRAW_SHAPE_SQUARE, _ACT_FNPTR(ActionAddSquare) },

	//////////////////////////////////////////////
	//Color actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_COL_BLACK, _ACT_FNPTR_COL(DWCOLOR_BLACK) },
	{ ACTION_DRAW_COL_YELLOW, _ACT_FNPTR_COL(DWCOLOR_YELLOW) },
	{ ACTION_DRAW_COL_ORANGE, _ACT_FNPTR_COL(DWCOLOR_ORANGE) },
	{ ACTION_DRAW_COL_RED, _ACT_FNPTR_COL(DWCOLOR_RED) },
	{ ACTION_DRAW_COL_GREEN, _ACT_FNPTR_COL(DWCOLOR_GREEN) },
	{ ACTION_DRAW_COL_BLUE, _ACT_FNPTR_COL(DWCOLOR_BLUE) },

	//////////////////////////////////////////////
	//Other actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_OTHER_EXIT, _ACT_FNPTR(ActionExit) }
};

std::map<ActionType, ActionData*> actionDataTable {
	//////////////////////////////////////////////
	//Shape actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_SHAPE_RECTANGLE, action_draw_shape_rectangle },
	{ ACTION_DRAW_SHAPE_SQUARE, action_draw_shape_square },
	{ ACTION_DRAW_SHAPE_TRIANGLE, action_draw_shape_triangle },
	{ ACTION_DRAW_SHAPE_HEXAGON, action_draw_shape_hexagon },
	{ ACTION_DRAW_SHAPE_CIRCLE, action_draw_shape_circle },

	//////////////////////////////////////////////
	//Color actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_COL_BLACK, action_draw_col_black },
	{ ACTION_DRAW_COL_YELLOW, action_draw_col_yellow },
	{ ACTION_DRAW_COL_ORANGE, action_draw_col_orange },
	{ ACTION_DRAW_COL_RED, action_draw_col_red },
	{ ACTION_DRAW_COL_GREEN, action_draw_col_green },
	{ ACTION_DRAW_COL_BLUE, action_draw_col_blue },

	//////////////////////////////////////////////
	//ColorMode actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_COLMODE_FILL, action_draw_colmode_fill },
	{ ACTION_DRAW_COLMODE_DRAW, action_draw_colmode_draw },

	//////////////////////////////////////////////
	//Other actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_OTHER_SELECT, action_draw_other_select },
	{ ACTION_DRAW_OTHER_MOVE, action_draw_other_move },
	{ ACTION_DRAW_OTHER_DELETE_FIG, action_draw_other_delete_fig },
	{ ACTION_DRAW_OTHER_CLEAR_ALL, action_draw_other_clear_all },
	{ ACTION_DRAW_OTHER_SAVE_GRAPH, action_draw_other_save_graph },
	{ ACTION_DRAW_OTHER_OPEN_GRAPH, action_draw_other_open_graph },
	{ ACTION_DRAW_OTHER_REC_START, action_draw_other_rec_start },
	{ ACTION_DRAW_OTHER_REC_STOP, action_draw_other_rec_stop },
	{ ACTION_DRAW_OTHER_REC_PAUSE, action_draw_other_rec_pause },
	{ ACTION_DRAW_OTHER_UNDO, action_draw_other_undo },
	{ ACTION_DRAW_OTHER_REDO, action_draw_other_redo },
	{ ACTION_DRAW_OTHER_PLAY, action_draw_other_play },
	{ ACTION_DRAW_OTHER_EXIT, action_draw_other_exit },

	//////////////////////////////////////////////
	//Play mode actions
	//////////////////////////////////////////////
	{ ACTION_PLAY_PICKHIDE_FIGTYPE, action_play_pickhide_figtype },
	{ ACTION_PLAY_PICKHIDE_FIGCOL, action_play_pickhide_figcol },
	{ ACTION_PLAY_PICKHIDE_FIGTYPE_COL, action_play_pickhide_figtype_col },
	{ ACTION_PLAY_OTHER_DRAW, action_play_other_draw }
};

void Application::Print(string msg) const
{
	m_Frontend->SetStatusBarText(msg);
}

ActionInstantiator Application::GetActionInstantiatorFromType(const ActionType& type)
{
	auto it = actionDataTable2.find(type);
	return it != actionDataTable2.end() ? it->second : 0;
}

Application::Application()
{
	//create IO
	m_Output = new Output(this);
	m_Input = m_Output->CreateInput();

	SetCurrentColorMode(DWCOLORMODE_DRAW);

	//set running
	m_IsRunning = true;

	//add the initial gfx info to the stack
	m_GfxStack.push(GfxInfo());

	//set initial gfx info
	SetGfxInfo();

	//create frontend
	m_Frontend = new UIFrontend;

	//initialize figure count
	m_FigureCount = 0;

	//zero out the figure pointers
	memset(m_FigureList, 0, sizeof(CFigure*) * MAX_FIGURE_COUNT);
}

Application::~Application()
{
	delete m_Output;
	delete m_Input;
	delete m_Frontend;

	//delete action data as well
	for (auto &x : actionDataTable)
	{
		delete x.second;
	}
}

bool Application::IsRunning() const
{
	return m_IsRunning;
}

void Application::Render()
{
	m_Frontend->Render();

	for (int i = 0; i < m_FigureCount; i++)
	{
		if (m_FigureList[i])
		{
			m_FigureList[i]->Draw(m_Output);
		}
	}
}

void Application::Loop()
{
	Point mousePos = m_Input->GetMousePos();

	if (m_LastMousePosition.x == 0 && m_LastMousePosition.y == 0)
	{
		m_LastMousePosition = mousePos;
	}

	int m0 = 0;
	bool mouseDown = m_Input->GetMouseDown();

	if (mouseDown)
	{
		if (!m_MouseDown)
		{
			m_MouseDown = true;

			//send mdown event
			UITouchEvent evt(mousePos.x, mousePos.y, UITouchEventType::Down);
			m_Frontend->HandleTouchEvent(&evt);
		}
	}
	else if (m_MouseDown)
	{
		m_MouseDown = false;

		//send mup event
		UITouchEvent evt(mousePos.x, mousePos.y, UITouchEventType::Up);
		m_Frontend->HandleTouchEvent(&evt);
	}

	if (mousePos.x != m_LastMousePosition.x || mousePos.y != m_LastMousePosition.y)
	{
		//send mdrag event
		UITouchEvent evt(mousePos.x, mousePos.y, UITouchEventType::Drag);
		m_Frontend->HandleTouchEvent(&evt);
	}

	//get current action
	/*ActionType action = m_Input->GetUserAction();

	DebugLog([action](DEBUG_LOG_PARAM) {
		stream << "Handling action: " << action << endl;
	});

	//check if action is a draw mode action
	if (IsDrawModeAction(action))
	{
		HandleDrawModeAction(action);
	}

	//manually handle other actions
	//handle the action
	switch (action)
	{
	case EXIT:
		Exit();
		break;

	default:
		break;
	}*/
}

void Application::SetGfxInfo(color drawColor, int borderWidth, bool fill, color fillColor, int fixedRadius)
{
	//set graphic info
	GfxInfo* gfx = GetGfxInfo();
	gfx->draw_col = drawColor;
	gfx->border_width = borderWidth;
	gfx->is_filled = fill;
	gfx->fill_col = fillColor;
	gfx->fixed_radius = fixedRadius;
}

GfxInfo* Application::GetGfxInfo()
{
	return &m_GfxStack.top();
}

void Application::PushGfxInfo(const GfxInfo& gfxInfo)
{
	m_GfxStack.push(gfxInfo);
}

void Application::PopGfxInfo()
{
	m_GfxStack.pop();
}

void Application::DebugLog(string msg, bool appendNewLine)
{
#ifdef ENABLE_DEBUG_LOG
	cout << "[DEBUG] " << msg;

	if (appendNewLine)
	{
		cout << endl;
	}
#endif
}

void Application::DebugLog(function<void(DEBUG_LOG_PARAM)> log)
{
	//create a string stream, log to it, then print to console
	stringstream stream;
	log(stream);

	DebugLog(stream.str(), false);
}

Output* Application::GetOutput()
{
	return m_Output;
}

Input* Application::GetInput()
{
	return m_Input;
}

UIFrontend* Application::GetUIFrontend()
{
	return m_Frontend;
}

void Application::HandleAction(const ActionType& type)
{
	DebugLog("Handling action...");

	//find action instantiator from type
	ActionInstantiator instantiator = GetActionInstantiatorFromType(type);
	if (instantiator)
	{
		//call instantiator and create action
		auto action = instantiator(this);

		//execute action
		action->Execute();
	}
}

void Application::Exit()
{
	DebugLog("Exiting the app");

	m_IsRunning = false;
}

DWColorModes Application::GetCurrentColorMode()
{
	return m_CurrentColorMode;
}

void Application::SetCurrentColorMode(DWColorModes colMode)
{
	m_CurrentColorMode = colMode;
}

void Application::SetDrawModeColor(DWColors col)
{
	color c;
	switch (col)
	{
	case DWCOLOR_BLACK:
		c = BLACK;
		break;

	case DWCOLOR_YELLOW:
		c = YELLOW;
		break;

	case DWCOLOR_ORANGE:
		c = ORANGE;
		break;

	case DWCOLOR_RED:
		c = RED;
		break;

	case DWCOLOR_GREEN:
		c = GREEN;
		break;

	case DWCOLOR_BLUE:
		c = BLUE;
		break;

	case DWCOLOR_COUNT:
		break;
	}

	switch (m_CurrentColorMode)
	{
	case DWCOLORMODE_FILL:
		GetGfxInfo()->fill_col = c;
		break;

	case DWCOLORMODE_DRAW:
		GetGfxInfo()->draw_col = c;
		break;

	case DWCOLORMODE_COUNT:
		break;
	}
}

void Application::SetCurrentMode(bool isPlayMode)
{
	m_Frontend->SetCurrentMode(isPlayMode);
}

void Application::AddFigure(CFigure* pFig)
{
	if (m_FigureCount < MAX_FIGURE_COUNT) 
	{
		m_FigureList[m_FigureCount++] = pFig;

		Render();
	}
}

CFigure* Application::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	return NULL;
}