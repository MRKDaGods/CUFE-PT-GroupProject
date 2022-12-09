#include "Application.h"

#include <map>
#include <iostream>
#include <sstream>

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

bool Application::IsDrawModeAction(const ActionType& action) const
{
	return action > ACTION_DRAW_SHAPE_BEGIN && action < ACTION_DRAW_SHAPE_END;
}

void Application::HandleDrawModeAction(const ActionType& type)
{
	DebugLog("Handling draw mode action...");

	//find action data from type
	ActionData* data = GetActionDataFromType(type);
	if (data)
	{
		//data found, invoke callback and set status bar message
		Print(data->status_bar_msg);

		data->callback(this, m_Input, m_Output);
	}
}

ActionData* Application::GetActionDataFromType(ActionType type)
{
	auto it = actionDataTable.find(type);
	return it != actionDataTable.end() ? it->second : 0;
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
		m_GfxInfo.fill_col = c;
		break;

	case DWCOLORMODE_DRAW:
		m_GfxInfo.draw_col = c;
		break;

	case DWCOLORMODE_COUNT:
		break;
	}
}

void Application::SetCurrentMode(bool isPlayMode)
{
	m_Frontend->SetCurrentMode(isPlayMode);
}

Application::Application()
{
	//create IO
	m_Output = new Output(this);
	m_Input = m_Output->CreateInput();

	SetCurrentColorMode(DWCOLORMODE_DRAW);

	//set running
	m_IsRunning = true;

	//set initial gfx info
	SetGfxInfo();

	//create frontend
	m_Frontend = new UIFrontend;
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
	m_GfxInfo.draw_col = drawColor;
	m_GfxInfo.border_width = borderWidth;
	m_GfxInfo.is_filled = fill;
	m_GfxInfo.fill_col = fillColor;
	m_GfxInfo.fixed_radius = fixedRadius;
}

GfxInfo* Application::GetGfxInfo()
{
	return &m_GfxInfo;
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

void Application::HandleAction(const ActionType& type)
{
	DebugLog("Handling action...");

	//find action data from type
	ActionData* data = GetActionDataFromType(type);
	if (data)
	{
		//data found, invoke callback and set status bar message
		Print(data->status_bar_msg);

		data->callback(this, m_Input, m_Output);
	}
}
