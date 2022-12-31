#pragma once

#include "../Action.h"

//forward declaration
class CFigure;

class ActionSelect : public Action
{
private:
	int m_SelectedID;

public:
	ActionSelect(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};