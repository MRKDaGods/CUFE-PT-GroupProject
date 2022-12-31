#include "ActionDrag.h"
#include "../../Application.h"

ActionDrag::ActionDrag(Application* app) : Action(app)
{
	m_InitialPoint = Point();
	m_Down = false;
}

void ActionDrag::ReadActionParameters()
{
	//display msg
	m_Frontend->SetStatusBarText("DRAG: Click a point inside the shape then start dragging");

	//keep reading mouse position until mouse is down
	do 
	{
		m_InitialPoint = m_Input->GetMousePos();
	} while (!m_Input->GetRealTimeMouseDown());

	//check if point is inside selected figure
	//no null checks, we know that SelectedFigure is not null
	//set down state to true if we clicked inside the figure
	m_Down = m_Application->GetSelectedFigure()->HitTest(m_InitialPoint);
}

void ActionDrag::Execute()
{
	//check for selection first
	CFigure* selectedFig = m_Application->GetSelectedFigure();

	//display error message if no figure is selected
	if (selectedFig == 0)
	{
		m_Frontend->SetStatusBarText("DRAG: No figure selected");
		return;
	}

	//check if we are initially down
	if (!m_Down) 
	{
		//display error
		m_Frontend->SetStatusBarText("DRAG: Shape not clicked");
		return;
	}

	//display start message
	m_Frontend->SetStatusBarText("DRAG: Started dragging");

	while (true) 
	{
		//get mouse position
		Point mousePos = m_Input->GetMousePos();

		//update down state
		m_Down = m_Input->GetRealTimeMouseDown() && selectedFig->HitTest(mousePos);

		//check if we released the mouse, dragging would stop here
		if (!m_Down) 
		{
			break;
		}

		//check if position hasnt changed from reference
		//if so skip
		if ((Vector2)mousePos == m_InitialPoint) 
		{
			continue;
		}

		//calculate delta between mousePos and reference
		int dx = mousePos.x - m_InitialPoint.x;
		int dy = mousePos.y - m_InitialPoint.y;

		//update reference
		m_InitialPoint = mousePos;

		//translate figure
		selectedFig->Translate(dx, dy);

		//just render our shapes
		m_Application->Render(true, false);
	}

	//display finish message
	m_Frontend->SetStatusBarText("DRAG: Stopped dragging");
}

ActionType ActionDrag::GetActionType()
{
    return ACTION_DRAW_EXTRA_DRAG;
}

bool ActionDrag::CanReadActionParameters()
{
	//can read if there is a selected figure
	return m_Application->GetSelectedFigure() != 0;
}
