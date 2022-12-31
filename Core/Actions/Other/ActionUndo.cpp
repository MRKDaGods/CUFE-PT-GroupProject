#include "ActionUndo.h"
#include "../../Application.h"

ActionUndo::ActionUndo(Application* app) : Action(app)
{
}

void ActionUndo::ReadActionParameters()
{
}

void ActionUndo::Execute()
{
	//index 0 -> most recent
	//get recent actions
	auto history = m_Application->GetActionHistory()->GetHistory();

	//check if there are any recents
	if (history->GetCount() == 0) return;

	//get most recent action
	Action* mostRecent = (*history)[0];

	//undo it
	mostRecent->Undo();

	//pop the circular buffer
	history->Pop();
}

ActionType ActionUndo::GetActionType()
{
	return ACTION_DRAW_OTHER_UNDO;
}
