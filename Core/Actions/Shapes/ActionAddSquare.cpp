#include "ActionAddSquare.h"
#include "../../Application.h"
#include "../../../Figures/CSquare.h"

ActionAddSquare::ActionAddSquare(Application* app) : Action(app)
{
	m_Center = Point();
}

void ActionAddSquare::ReadActionParameters()
{
	m_Frontend->SetStatusBarText("New Square: Click at center");

	//get center
	m_Input->GetPointClicked(m_Center.x, m_Center.y);

	//clear status bar
	m_Frontend->SetStatusBarText("");
}

//Execute the action
void ActionAddSquare::Execute()
{
	//read params
	ReadActionParameters();

	//create a square
	//gfxInfo should be a copy of Application::GetGfxInfo
	CSquare* sqr = new CSquare(m_Center, *m_Application->GetGfxInfo());

	//add square to the list of figures
	m_Application->AddFigure(sqr);
}
