#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

//Add Circle Action class
class ActionAddCircle : public Action
{
private:
	Point m_Center;
	Point m_Radius;
	int m_FigureID;
	GfxInfo m_GfxInfo;

public:
	ActionAddCircle(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override;
	virtual ActionType GetActionType() override;
};