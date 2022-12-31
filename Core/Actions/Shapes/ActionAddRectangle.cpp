#include "ActionAddRectangle.h"
#include "../../Application.h"
#include "../../../Figures/CRectangle.h"

ActionAddRectangle::ActionAddRectangle(Application* app) : Action(app)
{
	m_P1 = m_P2 = Point();

	m_Rectangle = 0;
}

void ActionAddRectangle::ReadActionParameters()
{
	//get first point
	m_Frontend->SetStatusBarText("New Rectangle: Click at first corner");
	m_Input->GetPointClicked(m_P1.x, m_P1.y);

	m_Frontend->SetStatusBarText("New Rectangle: Click at second corner");

	//get second point
	m_Input->GetPointClicked(m_P2.x, m_P2.y);

	//clear status bar
	m_Frontend->SetStatusBarText("");
}

void ActionAddRectangle::Execute()
{
	//create a rectangle
	//gfxInfo should be a copy of Application::GetGfxInfo
	m_Rectangle = new CRectangle(m_P1, m_P2, *m_Application->GetGfxInfo());

	//add the rectangle to the list of figures
	m_Application->AddFigure(m_Rectangle);
}

void ActionAddRectangle::Undo()
{
	m_Application->DeleteFigure(m_Rectangle);
	m_Application->Render(true); //re-render
}

ActionType ActionAddRectangle::GetActionType()
{
	return ACTION_DRAW_SHAPE_RECTANGLE;
}
