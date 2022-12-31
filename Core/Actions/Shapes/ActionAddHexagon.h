#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

//Add Hexagon Action class
class ActionAddHexagon : public Action
{
private:
	Point m_Center;
	int m_FigureID;
	GfxInfo m_GfxInfo;

public:
	ActionAddHexagon(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override;
	virtual ActionType GetActionType() override;
};