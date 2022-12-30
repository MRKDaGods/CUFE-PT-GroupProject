#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

class CCircle;

//Add Circle Action class
class ActionAddCircle : public Action
{
private:
	Point m_Center;
	Point m_Radius;
	CCircle* m_Circle;

public:
	ActionAddCircle(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override;
	virtual ActionType GetActionType() override;
};