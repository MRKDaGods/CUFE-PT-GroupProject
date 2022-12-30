#include "ActionSetColorMode.h"
#include "../../Application.h"

ActionSetColorMode::ActionSetColorMode(Application* app, DWColorModes mode) : Action(app)
{
	m_ColorMode = mode;
	m_OldMode = m_Application->GetCurrentColorMode();
}

void ActionSetColorMode::SetColorMode(DWColorModes mode)
{
	//set gfx info is filled to true if m_ColorMode is DWCOLORMODE_FULL
	bool isFill = mode == DWCOLORMODE_FILL;
	m_Application->GetGfxInfo()->is_filled = isFill;

	//update color mode in application
	m_Application->SetCurrentColorMode(mode);

	char buf[100];
	sprintf(buf, "COLOR MODE: Set color mode to %s", isFill ? "FILLED" : "NON-FILLED");

	m_Frontend->SetStatusBarText(buf);
}

void ActionSetColorMode::ReadActionParameters()
{
}

void ActionSetColorMode::Execute()
{
	SetColorMode(m_ColorMode);
}

void ActionSetColorMode::Undo()
{
	//update frontend as well
	m_Frontend->SetSelectedColorMode(m_OldMode);

	//set the old mode
	SetColorMode(m_OldMode);
}

ActionType ActionSetColorMode::GetActionType()
{
	return m_ColorMode == DWCOLORMODE_FILL ? ACTION_DRAW_COLMODE_FILL : ACTION_DRAW_COLMODE_DRAW;
}
