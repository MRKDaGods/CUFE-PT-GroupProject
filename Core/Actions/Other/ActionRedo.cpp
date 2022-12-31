#include "ActionRedo.h"
#include "../../Application.h"

ActionRedo::ActionRedo(Application* app) : Action(app)
{
}

void ActionRedo::ReadActionParameters()
{
}

void ActionRedo::Execute()
{
	//dont continue if last action is null or it is not undo or redo
	Action* lastAction = m_Application->GetActionHistory()->GetLastAction();
	if (lastAction == 0 || (lastAction->GetActionType() != ACTION_DRAW_OTHER_UNDO && lastAction->GetActionType() != ACTION_DRAW_OTHER_REDO)) return;

	//get history and then peek next
	auto history = m_Application->GetActionHistory()->GetHistory();
	
	Action* nextAction = history->PeekNext();
	if (nextAction != 0)
	{
		//handle action
		nextAction->Execute();

		//put back in history
		history->Push(nextAction, false);
	}
}

ActionType ActionRedo::GetActionType()
{
	return ACTION_DRAW_OTHER_REDO;
}