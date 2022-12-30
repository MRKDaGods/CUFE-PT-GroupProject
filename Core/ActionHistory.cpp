#include "ActionHistory.h"
#include "../Common.h"

#ifdef ENABLE_DEBUG_LOG
#include <iostream>
#endif

ActionHistory::ActionHistory(Application* app)
{
	m_Application = app;

	//init actions buffer with our cleanup handler
	m_Actions = new CircularBuffer<Action*, 5>(&ActionHistory::OnActionRemoved);

	//null out last action
	m_LastAction = 0;
}

ActionHistory::~ActionHistory()
{
	delete m_Actions;
}

bool ActionHistory::IsActionSupported(Action* action)
{
	//unsupported if null
	if (action == 0) return false;

	return action->IsAddFigureAction()
		|| action->IsChangeColorAction()
		|| action->IsChangeColorModeAction()
		|| action->GetActionType() == ACTION_DRAW_OTHER_DELETE_FIG
		|| action->GetActionType() == ACTION_DRAW_OTHER_MOVE;
}

void ActionHistory::OnActionRemoved(Action** action)
{
	if (*action != 0)
	{
#ifdef ENABLE_DEBUG_LOG
		std::cout << "[Action history] Cleaning action of type " << (*action)->GetActionType() << '\n';
#endif

		//delete action to prevent memory leaks
		delete *action;
	}
}

bool ActionHistory::AddAction(Action* action)
{
	//dont record anything if action is null
	if (action == 0) return false;

	//delete last action if it's not null and if it was an unsupported one (not stored in history)
	if (m_LastAction != 0 && !IsActionSupported(m_LastAction))
	{
		delete m_LastAction;
	}

	//store last action regardless of type
	m_LastAction = action;

	//record action if it is one of the desired types
	//Add Figure, Delete Figure, Change Color, and Move

	if (IsActionSupported(action))
	{
		m_Actions->Push(action);
		return true;
	}

	return false;
}

void ActionHistory::Clear()
{
	//zero out last action
	m_LastAction = 0;

	//reset circular buffer
	m_Actions->Reset();
}

CircularBuffer<Action*, 5>* ActionHistory::GetHistory()
{
	return m_Actions;
}

Action* ActionHistory::GetLastAction()
{
	return m_LastAction;
}
