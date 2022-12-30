#include "ActionAddSquare.h"
#include "../../Application.h"
#include "../../../Figures/CSquare.h"

ActionAddSquare::ActionAddSquare(Application* app) : Action(app)
{
	m_Center = Point();

	m_Square = 0;
}

void ActionAddSquare::ReadActionParameters()
{
	//get center
	m_Frontend->SetStatusBarText("New Square: Click at center");
	m_Input->GetPointClicked(m_Center.x, m_Center.y);

	//clear status bar
	m_Frontend->SetStatusBarText("");
}

void ActionAddSquare::Execute()
{
	//create a square
	//gfxInfo should be a copy of Application::GetGfxInfo
	m_Square = new CSquare(m_Center, *m_Application->GetGfxInfo());

	//add square to the list of figures
	m_Application->AddFigure(m_Square);
}

void ActionAddSquare::Undo()
{
	m_Application->DeleteFigure(m_Square);
	m_Application->Render(true); //re-render
}

ActionType ActionAddSquare::GetActionType()
{
	return ACTION_DRAW_SHAPE_SQUARE;
}
