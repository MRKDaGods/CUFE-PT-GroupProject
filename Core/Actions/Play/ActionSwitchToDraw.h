#pragma once

#include "../Action.h"

class ActionSwitchToDraw : public Action
{
public:
	ActionSwitchToDraw(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};