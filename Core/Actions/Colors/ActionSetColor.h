#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

class ActionSetColor : public Action
{
private:
	DWColors m_Color;

public:
	ActionSetColor(Application* app, DWColors color);

	//Reads rectangle parameters
	virtual void ReadActionParameters() override;

	//Add rectangle to the ApplicationManager
	virtual void Execute() override;
};