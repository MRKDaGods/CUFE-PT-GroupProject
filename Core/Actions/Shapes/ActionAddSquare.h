#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

class CSquare;

//Add Square Action class
class ActionAddSquare : public Action
{
private:
	Point m_Center;
	CSquare* m_Square;

public:
	ActionAddSquare(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override;
	virtual ActionType GetActionType() override;
};