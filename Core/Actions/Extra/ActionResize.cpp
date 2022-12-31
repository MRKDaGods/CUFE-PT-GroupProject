#include "ActionResize.h"
#include "../../Application.h"
#include "../../../Figures/FigureNode.h"

ActionResize::ActionResize(Application* app) : Action(app)
{
	m_InitialPoint = Point();
	m_Down = false;

	m_Node = 0;
}

void ActionResize::ReadActionParameters()
{
	//display msg
	m_Frontend->SetStatusBarText("RESIZE: Hold one of the nodes to start dragging");

	//no null checks, we know that SelectedFigure is not null
	CFigure* selectedFig = m_Application->GetSelectedFigure();

	//enable figure nodes
	selectedFig->SetNodeRenderingState(true);

	//just re-render figures
	m_Application->Render(false, false);

	//keep reading mouse position until mouse is down
	do
	{
		m_InitialPoint = m_Input->GetMousePos();
	} while (!m_Input->GetRealTimeMouseDown());

	m_Node = selectedFig->GetNode(m_InitialPoint);

	//check if point is inside selected figure
	//set down state to true if we clicked inside the figure
	m_Down = m_Node != 0;
}

void ActionResize::Execute()
{
	//check for selection first
	CFigure* selectedFig = m_Application->GetSelectedFigure();

	//display error message if no figure is selected
	if (selectedFig == 0)
	{
		m_Frontend->SetStatusBarText("RESIZE: No figure selected");
		return;
	}

	//check if we are initially down
	if (!m_Down)
	{
		//display error
		m_Frontend->SetStatusBarText("RESIZE: No node clicked");

		//remove node
		selectedFig->SetNodeRenderingState(false);

		//update
		m_Application->Render(true);

		return;
	}

	//display start message
	m_Frontend->SetStatusBarText("RESIZE: Started resizing");

	//get fig pos, it's constant
	Vector2 figPos = selectedFig->GetPosition();

	while (true)
	{
		//get mouse position
		Point mousePos = m_Input->GetMousePos();

		//update down state
		m_Down = m_Input->GetRealTimeMouseDown(); //&& selectedFig->HitTest(mousePos);

		//check if we released the mouse, resizing would stop here
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

		m_Node->SetPosition(mousePos);

		//update reference
		m_InitialPoint = mousePos;

		//translate figure
		selectedFig->Resize(m_Node);

		//just render our shapes
		m_Application->Render(true, false);
	}

	//turn off nodes
	selectedFig->SetNodeRenderingState(false);

	//update
	m_Application->Render(true);

	//display finish message
	m_Frontend->SetStatusBarText("RESIZE: Stopped resizing");
}

ActionType ActionResize::GetActionType()
{
	return ACTION_DRAW_EXTRA_RESIZE;
}

bool ActionResize::CanReadActionParameters()
{
	//can read if there is a selected figure
	return m_Application->GetSelectedFigure() != 0;
}
