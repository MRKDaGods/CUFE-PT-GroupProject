#pragma once

#include "../Action.h"

class ActionRedo : public Action
{
public:
	ActionRedo(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};