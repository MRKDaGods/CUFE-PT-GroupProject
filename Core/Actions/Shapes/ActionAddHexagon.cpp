#include "ActionAddHexagon.h"
#include "../../Application.h"
#include "../../../Figures/CHexagon.h"

ActionAddHexagon::ActionAddHexagon(Application* app) : Action(app)
{
	m_Center = Point();

	m_Hexagon = 0;
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
	m_Hexagon = new CHexagon(m_Center, *m_Application->GetGfxInfo());

	//add hexagon to the list of figures
	m_Application->AddFigure(m_Hexagon);
}

void ActionAddHexagon::Undo()
{
	m_Application->DeleteFigure(m_Hexagon);
	m_Application->Render(true); //re-render
}

ActionType ActionAddHexagon::GetActionType()
{
	return ACTION_DRAW_SHAPE_HEXAGON;
}
