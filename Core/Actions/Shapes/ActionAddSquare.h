#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

//Add Square Action class
class ActionAddSquare : public Action
{
private:
	Point m_Center;
	int m_FigureID;
	GfxInfo m_GfxInfo;

public:
	ActionAddSquare(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override;
	virtual ActionType GetActionType() override;
};