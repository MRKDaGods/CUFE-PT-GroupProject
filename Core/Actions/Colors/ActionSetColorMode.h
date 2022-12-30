#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

class ActionSetColorMode : public Action
{
private:
	DWColorModes m_ColorMode;
	DWColorModes m_OldMode;

	//Sets the current color mode
	void SetColorMode(DWColorModes mode);

public:
	ActionSetColorMode(Application* app, DWColorModes mode);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override;
	virtual ActionType GetActionType() override;
};