#include "ActionAddTriangle.h"
#include "../../Application.h"
#include "../../../Figures/CTriangle.h"

ActionAddTriangle::ActionAddTriangle(Application* app) : Action(app)
{
	m_P1 = m_P2 = m_P3 = Point();

	//the figure ID
	m_FigureID = m_Application->AllocateFigureID();
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
	m_GfxInfo = *m_Application->GetGfxInfo();
	CTriangle* tri = new CTriangle(m_FigureID, m_P1, m_P2, m_P3, m_GfxInfo);

	//add triangle to the list of figures
	m_Application->AddFigure(tri);
}

void ActionAddTriangle::Undo()
{
	CFigure* fig = m_Application->GetFigureWithID(m_FigureID);
	if (fig != 0)
	{
		m_Application->DeleteFigure(fig);
		m_Application->Render(true); //re-render
	}
}

ActionType ActionAddTriangle::GetActionType()
{
	return ACTION_DRAW_SHAPE_TRIANGLE;
}
