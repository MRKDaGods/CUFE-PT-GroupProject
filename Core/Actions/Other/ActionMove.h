#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

class CFigure;

class ActionMove : public Action
{
private:
	Point m_Destination;
	int m_Dx;
	int m_Dy;
	int m_MovedID;

public:
	ActionMove(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override;
	virtual ActionType GetActionType() override;
	virtual bool CanReadActionParameters() override;
};