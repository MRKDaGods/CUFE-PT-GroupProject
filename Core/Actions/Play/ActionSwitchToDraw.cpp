#include "ActionSwitchToDraw.h"
#include "../../Application.h"

ActionSwitchToDraw::ActionSwitchToDraw(Application* app) : Action(app)
{
}

void ActionSwitchToDraw::ReadActionParameters()
{
}

void ActionSwitchToDraw::Execute()
{
	//switch modes
	m_Application->SetCurrentMode(false);

	//restore graph
	m_Application->GetGraph()->Restore();

	//set status bar msg
	m_Frontend->SetStatusBarText("PLAY MODE: Switched to draw mode");
}

ActionType ActionSwitchToDraw::GetActionType()
{
	return ACTION_PLAY_OTHER_DRAW;
}
