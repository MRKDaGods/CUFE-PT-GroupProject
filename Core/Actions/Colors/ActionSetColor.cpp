#include "ActionSetColor.h"

#include "../../Application.h"

ActionSetColor::ActionSetColor(Application* app, DWColors color) : Action(app)
{
	m_Color = color;
}

void ActionSetColor::ReadActionParameters()
{
}

void ActionSetColor::Execute()
{
	//set color
	m_Application->SetDrawModeColor(m_Color);
}
