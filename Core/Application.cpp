#include "Application.h"

#include <map>
#include <iostream>
#include <sstream>

std::map<ActionType, ActionData*> actionDataTable {
	{ ACTION_DRAW_RECTANGLE, action_draw_rectangle },
	{ ACTION_DRAW_SQUARE, action_draw_square },
	{ ACTION_DRAW_TRIANGLE, action_draw_triangle },
	{ ACTION_DRAW_HEXAGON, action_draw_hexagon },
	{ ACTION_DRAW_CIRCLE, action_draw_circle },
};

void Application::Print(string msg) const
{
	m_Frontend->SetStatusBarText(msg);
}

bool Application::IsDrawModeAction(const ActionType& action) const
{
	return action > ACTION_DRAW_BEGIN && action < ACTION_DRAW_END;
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

Application::Application()
{
	//create IO
	m_Output = new Output(this);
	m_Input = m_Output->CreateInput();

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
	cout << "[DEBUG] " << msg;

	if (appendNewLine)
	{
		cout << endl;
	}
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
