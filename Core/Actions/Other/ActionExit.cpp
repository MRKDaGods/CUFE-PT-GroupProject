#include "ActionExit.h"

#include "../../../Core/Application.h"

ActionExit::ActionExit(Application* app) : Action(app)
{
}

void ActionExit::ReadActionParameters()
{
}

void ActionExit::Execute()
{
	//exit the app
	m_Application->Exit();
}

ActionType ActionExit::GetActionType()
{
	return ACTION_DRAW_OTHER_EXIT;
}
