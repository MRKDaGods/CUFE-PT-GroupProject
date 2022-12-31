#include "ActionSelect.h"

#include "../../../Core/Application.h"
#include "../../../Figures/CFigure.h"

ActionSelect::ActionSelect(Application* app) : Action(app)
{
	m_SelectedID = -1;
}

void ActionSelect::ReadActionParameters()
{
	m_Frontend->SetStatusBarText("Select Shape: Select a shape");

	//get the clicked point
	Point buf;
	m_Input->GetPointClicked(buf.x, buf.y);

	//find figure, null if not found
	CFigure* fig = m_Application->GetFigure(buf.x, buf.y);
	if (fig != 0)
	{
		m_SelectedID = fig->GetID();
	}
}

void ActionSelect::Execute()
{
	//if selected fig is null, just ignore
	CFigure* selectedFig = m_Application->GetFigureWithID(m_SelectedID);
	if (selectedFig == 0)
	{
		m_Frontend->SetStatusBarText("");
		return;
	}

	//if fig is already selected, unselect it
	if (selectedFig->IsSelected())
	{
		//unselect
		selectedFig->SetSelected(false);

		//update selected fig in application
		m_Application->SetSelectedFigure(0);

		//clear status bar text incase info was printed
		m_Frontend->SetStatusBarText("");
	}
	else
	{
		//get old selected figure, and unselect it if it is not null
		CFigure* oldSelected = m_Application->GetSelectedFigure();
		if (oldSelected != 0)
		{
			oldSelected->SetSelected(false);
		}

		//mark figure selected
		selectedFig->SetSelected(true);

		//update selected fig in application
		m_Application->SetSelectedFigure(selectedFig);

		//print figure info
		selectedFig->PrintInfo(m_Frontend);
	}

	//notify application to update
	m_Application->Render();
}

ActionType ActionSelect::GetActionType()
{
	return ACTION_DRAW_OTHER_SELECT;
}
