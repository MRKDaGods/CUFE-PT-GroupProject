#include "ActionAddHexagon.h"
#include "../../Application.h"
#include "../../../Figures/CHexagon.h"

ActionAddHexagon::ActionAddHexagon(Application* app) : Action(app)
{
	m_Center = Point();

	//the figure ID
	m_FigureID = m_Application->AllocateFigureID();
}

void ActionAddHexagon::ReadActionParameters()
{
	//get center
	m_Frontend->SetStatusBarText("New Hexagon: Click at center");
	m_Input->GetPointClicked(m_Center.x, m_Center.y);

	//clear status bar
	m_Frontend->SetStatusBarText("");
}

void ActionAddHexagon::Execute()
{
	//create a hexagon
	//gfxInfo should be a copy of Application::GetGfxInfo
	m_GfxInfo = *m_Application->GetGfxInfo();
	CHexagon* hex = new CHexagon(m_FigureID, m_Center, m_GfxInfo);

	//add hexagon to the list of figures
	m_Application->AddFigure(hex);
}

void ActionAddHexagon::Undo()
{
	CFigure* fig = m_Application->GetFigureWithID(m_FigureID);
	if (fig != 0)
	{
		m_Application->DeleteFigure(fig);
		m_Application->Render(true); //re-render
	}
}

ActionType ActionAddHexagon::GetActionType()
{
	return ACTION_DRAW_SHAPE_HEXAGON;
}
