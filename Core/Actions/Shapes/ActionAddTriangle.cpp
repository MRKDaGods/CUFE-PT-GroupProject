#include "ActionAddTriangle.h"
#include "../../Application.h"
#include "../../../Figures/CTriangle.h"

ActionAddTriangle::ActionAddTriangle(Application* app) : Action(app)
{
	m_P1 = m_P2 = m_P3 = Point();

	m_Triangle = 0;
}

void ActionAddTriangle::ReadActionParameters()
{
	//get p1
	m_Frontend->SetStatusBarText("New Triangle: Click at first corner");
	m_Input->GetPointClicked(m_P1.x, m_P1.y);

	//get p2
	m_Frontend->SetStatusBarText("New Triangle: Click at second corner");
	m_Input->GetPointClicked(m_P2.x, m_P2.y);

	//get p3
	m_Frontend->SetStatusBarText("New Triangle: Click at third corner");
	m_Input->GetPointClicked(m_P3.x, m_P3.y);

	//clear status bar
	m_Frontend->SetStatusBarText("");
}

void ActionAddTriangle::Execute()
{
	//create a triangle
	//gfxInfo should be a copy of Application::GetGfxInfo
	m_Triangle = new CTriangle(m_P1, m_P2, m_P3, *m_Application->GetGfxInfo());

	//add triangle to the list of figures
	m_Application->AddFigure(m_Triangle);
}

void ActionAddTriangle::Undo()
{
	m_Application->DeleteFigure(m_Triangle);
	m_Application->Render(true); //re-render
}

ActionType ActionAddTriangle::GetActionType()
{
	return ACTION_DRAW_SHAPE_TRIANGLE;
}
