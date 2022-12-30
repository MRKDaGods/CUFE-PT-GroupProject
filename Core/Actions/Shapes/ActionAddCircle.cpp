#include "ActionAddCircle.h"
#include "../../Application.h"
#include "../../../Figures/CCircle.h"

ActionAddCircle::ActionAddCircle(Application* app) : Action(app)
{
	m_Center = m_Radius = Point();
	m_Circle = 0;
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
	m_Circle = new CCircle(m_Center, m_Radius, *m_Application->GetGfxInfo());

	//add circle to the list of figures
	m_Application->AddFigure(m_Circle);
}

void ActionAddCircle::Undo()
{
	m_Application->DeleteFigure(m_Circle);
	m_Application->Render(true); //re-render
}

ActionType ActionAddCircle::GetActionType()
{
	return ACTION_DRAW_SHAPE_CIRCLE;
}
