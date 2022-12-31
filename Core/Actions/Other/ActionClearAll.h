#pragma once

#include "../Action.h"

class ActionClearAll : public Action
{
public:
	ActionClearAll(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};