#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

class CHexagon;

//Add Hexagon Action class
class ActionAddHexagon : public Action
{
private:
	Point m_Center;
	CHexagon* m_Hexagon;

public:
	ActionAddHexagon(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override;
	virtual ActionType GetActionType() override;
};