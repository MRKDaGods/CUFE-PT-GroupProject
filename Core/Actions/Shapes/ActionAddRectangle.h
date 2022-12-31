#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

class CRectangle;

//Add Rectangle Action class
class ActionAddRectangle : public Action
{
private:
	Point m_P1;
	Point m_P2;
	CRectangle* m_Rectangle;

public:
	ActionAddRectangle(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override;
	virtual ActionType GetActionType() override;
};