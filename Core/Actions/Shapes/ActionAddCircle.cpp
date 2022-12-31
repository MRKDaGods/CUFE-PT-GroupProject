#include "ActionAddCircle.h"
#include "../../Application.h"
#include "../../../Figures/CCircle.h"

ActionAddCircle::ActionAddCircle(Application* app) : Action(app)
{
	m_Center = m_Radius = Point();
	
	//the figure ID
	m_FigureID = m_Application->AllocateFigureID();
}

void ActionAddCircle::ReadActionParameters()
{
	//get center
	m_Frontend->SetStatusBarText("New Square: Click at center");
	m_Input->GetPointClicked(m_Center.x, m_Center.y);

	//get radius
	m_Frontend->SetStatusBarText("New Square: Click at radius point");
	m_Input->GetPointClicked(m_Radius.x, m_Radius.y);

	//clear status bar
	m_Frontend->SetStatusBarText("");
}

void ActionAddCircle::Execute()
{
	//create a circle
	//gfxInfo should be a copy of Application::GetGfxInfo

	m_GfxInfo = *m_Application->GetGfxInfo();
	CCircle* circle = new CCircle(m_FigureID, m_Center, m_Radius, m_GfxInfo);

	//add circle to the list of figures
	m_Application->AddFigure(circle);
}

void ActionAddCircle::Undo()
{
	CFigure* fig = m_Application->GetFigureWithID(m_FigureID);
	if (fig != 0) 
	{
		m_Application->DeleteFigure(fig);
		m_Application->Render(true); //re-render
	}
}

ActionType ActionAddCircle::GetActionType()
{
	return ACTION_DRAW_SHAPE_CIRCLE;
}
