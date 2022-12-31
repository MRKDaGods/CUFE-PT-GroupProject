#include "ActionMove.h"

#include "../../../Core/Application.h"
#include "../../../Figures/CFigure.h"

ActionMove::ActionMove(Application* app) : Action(app)
{
	m_Destination = Point();
	m_Dx = m_Dy = 0;

	m_MovedID = -1;
	//check for selection first
	CFigure* selectedFig = m_Application->GetSelectedFigure();

	if (selectedFig != 0)
	{
		m_MovedID = selectedFig->GetID();
	}
}

void ActionMove::ReadActionParameters()
{
	//get destination point
	m_Frontend->SetStatusBarText("MOVE: Click destination point");
	m_Input->GetPointClicked(m_Destination.x, m_Destination.y);

	//clear
	m_Frontend->SetStatusBarText("");
}

void ActionMove::Execute()
{
	//check for selection first
	CFigure* selectedFig = m_Application->GetFigureWithID(m_MovedID);

	//display error message if no figure is selected
	if (selectedFig == 0)
	{
		m_Frontend->SetStatusBarText("MOVE: No figure selected");
		return;
	}

	//translate figure by dx and dy
	Point figPos = selectedFig->GetPosition();
	m_Dx = m_Destination.x - figPos.x;
	m_Dy = m_Destination.y - figPos.y;

	//translate the figure
	selectedFig->Translate(m_Dx, m_Dy);

	char buf[100];
	sprintf(buf, "MOVE: Figured by %d to the left and %d to the bottom", m_Dx, m_Dy);
	m_Frontend->SetStatusBarText(buf);

	//notify application to update again and clear drawing area
	m_Application->Render(true);
}

void ActionMove::Undo()
{
	//2 checks
	//Moved figure not null AND it still exists in figure list, as it might have been deleted
	CFigure* movedFig = m_Application->GetFigureWithID(m_MovedID);
	if (movedFig != 0)
	{
		//found it, now translate inversely
		movedFig->Translate(-m_Dx, -m_Dy);

		//notify application to update again and clear drawing area
		m_Application->Render(true);
	}
}

ActionType ActionMove::GetActionType()
{
	return ACTION_DRAW_OTHER_MOVE;
}

bool ActionMove::CanReadActionParameters()
{
	//can read if there is a selected figure
	return m_Application->GetSelectedFigure() != 0;
}
