#include "ActionAddRectangle.h"
#include "../../Application.h"
#include "../../../Figures/CRectangle.h"

ActionAddRectangle::ActionAddRectangle(Application* app) : Action(app)
{
	m_P1 = m_P2 = Point();
}

void ActionAddRectangle::ReadActionParameters()
{
	m_Frontend->SetStatusBarText("New Rectangle: Click at first corner");

	//get first point
	m_Input->GetPointClicked(m_P1.x, m_P1.y);

	m_Frontend->SetStatusBarText("New Rectangle: Click at second corner");

	//get second point
	m_Input->GetPointClicked(m_P2.x, m_P2.y);

	//clear status bar
	m_Frontend->SetStatusBarText("");
}

//Execute the action
void ActionAddRectangle::Execute()
{
	//read params
	ReadActionParameters();

	//create a rectangle
	//gfxInfo should be a copy of Application::GetGfxInfo
	CRectangle* rect = new CRectangle(m_P1, m_P2, *m_Application->GetGfxInfo());

	//add the rectangle to the list of figures
	m_Application->AddFigure(rect);
}
