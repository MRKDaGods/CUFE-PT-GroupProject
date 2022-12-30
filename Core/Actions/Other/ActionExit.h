#pragma once

#include "../Action.h"

class ActionExit : public Action
{
public:
	ActionExit(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};