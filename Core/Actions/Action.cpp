#include "Action.h"
#include "../Application.h"

Action::Action(Application* app)
{
	m_Application = app;

	m_Output = m_Application->GetOutput();
	m_Input = m_Application->GetInput();
	m_Frontend = m_Application->GetUIFrontend();
}

void Action::Undo()
{
}

bool Action::CanReadActionParameters()
{
	return true;
}

bool Action::IsAddFigureAction()
{
	ActionType type = GetActionType();
	return type > ACTION_DRAW_SHAPE_BEGIN && type < ACTION_DRAW_SHAPE_END;
}

bool Action::IsChangeColorAction()
{
	ActionType type = GetActionType();
	return type > ACTION_DRAW_COL_BEGIN && type < ACTION_DRAW_COL_END;
}

bool Action::IsChangeColorModeAction()
{
	ActionType type = GetActionType();
	return type > ACTION_DRAW_COLMODE_BEGIN && type < ACTION_DRAW_COLMODE_END;
}

void Action::SetRecorded(bool recorded)
{
	m_IsRecorded = recorded;
}

bool Action::IsRecorded()
{
	return m_IsRecorded;
}
