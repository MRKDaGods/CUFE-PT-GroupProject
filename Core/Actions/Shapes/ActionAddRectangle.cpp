#include "ActionAddRectangle.h"
#include "../../Application.h"
#include "../../../Figures/CRectangle.h"

ActionAddRectangle::ActionAddRectangle(Application* app) : Action(app)
{
	m_P1 = m_P2 = Point();

	//the figure ID
	m_FigureID = m_Application->AllocateFigureID();
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
	m_GfxInfo = *m_Application->GetGfxInfo();
	CRectangle* rect = new CRectangle(m_FigureID, m_P1, m_P2, m_GfxInfo);

	//add the rectangle to the list of figures
	m_Application->AddFigure(rect);
}

void ActionAddRectangle::Undo()
{
	CFigure* fig = m_Application->GetFigureWithID(m_FigureID);
	if (fig != 0)
	{
		m_Application->DeleteFigure(fig);
		m_Application->Render(true); //re-render
	}
}

ActionType ActionAddRectangle::GetActionType()
{
	return ACTION_DRAW_SHAPE_RECTANGLE;
}
