#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

class CTriangle;

//Add Triangle Action class
class ActionAddTriangle : public Action
{
private:
	Point m_P1;
	Point m_P2;
	Point m_P3;
	CTriangle* m_Triangle;

public:
	ActionAddTriangle(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override;
	virtual ActionType GetActionType() override;
};