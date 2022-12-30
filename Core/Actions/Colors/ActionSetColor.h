#pragma once

#include "../Action.h"

class ActionSetColor : public Action
{
private:
	DWColors m_Color;
	DWColors m_OldColor;

	//The color mode at the time of the instantiation of the action
	DWColorModes m_ColorMode;
	bool m_OldFillState;

	//Sets the current color
	void SetColor(DWColors col, bool restoreFillState);

public:
	ActionSetColor(Application* app, DWColors color);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override;
	virtual ActionType GetActionType() override;
};