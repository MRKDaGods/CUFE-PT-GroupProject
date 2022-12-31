#include "ActionAddSquare.h"
#include "../../Application.h"
#include "../../../Figures/CSquare.h"

ActionAddSquare::ActionAddSquare(Application* app) : Action(app)
{
	m_Center = Point();

	//the figure ID
	m_FigureID = m_Application->AllocateFigureID();
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
	m_GfxInfo = *m_Application->GetGfxInfo();
	CSquare* sqr = new CSquare(m_FigureID, m_Center, m_GfxInfo);

	//add square to the list of figures
	m_Application->AddFigure(sqr);
}

void ActionAddSquare::Undo()
{
	CFigure* fig = m_Application->GetFigureWithID(m_FigureID);
	if (fig != 0)
	{
		m_Application->DeleteFigure(fig);
		m_Application->Render(true); //re-render
	}
}

ActionType ActionAddSquare::GetActionType()
{
	return ACTION_DRAW_SHAPE_SQUARE;
}
