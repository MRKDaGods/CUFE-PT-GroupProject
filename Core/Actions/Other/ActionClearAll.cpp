#include "ActionClearAll.h"

#include "../../../Core/Application.h"
#include "../../../GUI/Frontend/UIFrontend.h"
#include "../../../Figures/CFigure.h"

ActionClearAll::ActionClearAll(Application* app) : Action(app)
{
}

void ActionClearAll::ReadActionParameters()
{
}

void ActionClearAll::Execute()
{
	//reset colors
	//we can just invoke our frontend's buttons' handlers
	m_Frontend->Reset();

	//delete all figures
	m_Application->DeleteAllFigures();

	//set selected figure to null
	m_Application->SetSelectedFigure(0);

	//clear history
	m_Application->GetActionHistory()->Clear();

	//update interface
	m_Application->Render(true);

	m_Frontend->SetStatusBarText("CLEAR ALL: Successfully cleared everything");
}

ActionType ActionClearAll::GetActionType()
{
	return ACTION_DRAW_OTHER_CLEAR_ALL;
}
