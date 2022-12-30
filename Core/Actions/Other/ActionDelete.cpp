#include "ActionDelete.h"

#include "../../../Core/Application.h"
#include "../../../Figures/CFigure.h"

ActionDelete::ActionDelete(Application* app) : Action(app)
{
	m_DeletedFigure = 0;
}

ActionDelete::~ActionDelete()
{
	//okay so check whether the figure is displayed or not, if not delete it
	if (m_DeletedFigure != 0 && !m_Application->ContainsFigure(m_DeletedFigure))
	{
		delete m_DeletedFigure;
		m_DeletedFigure = 0;
	}
}

void ActionDelete::ReadActionParameters()
{
}

void ActionDelete::Execute()
{
	CFigure* selectedFig = m_Application->GetSelectedFigure();
	
	//display error message if no figure is selected
	if (selectedFig == 0)
	{
		m_Frontend->SetStatusBarText("DELETE: No figure selected");
		return;
	}

	//unselect it, incase restored later
	selectedFig->SetSelected(false);

	//dont delete underlying pointer, delete it in our destructor if it isnt restored
	//this action is destroyed when it goes out of scope in the action history
	m_DeletedFigure = selectedFig;
	m_Application->DeleteFigure(selectedFig, false);

	//clear selected fig in application
	m_Application->SetSelectedFigure(0);

	m_Frontend->SetStatusBarText("DELETE: Deleted figure");

	//notify application to update again and clear drawing area
	m_Application->Render(true);
}

void ActionDelete::Undo()
{
	if (m_DeletedFigure != 0)
	{
		//we need to restore the figure
		//AddFigure calls render so no need to update interface
		m_Application->AddFigure(m_DeletedFigure, true);
	}
}

ActionType ActionDelete::GetActionType()
{
	return ACTION_DRAW_OTHER_DELETE_FIG;
}
