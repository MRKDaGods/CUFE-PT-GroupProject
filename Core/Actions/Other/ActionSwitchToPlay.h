#pragma once

#include "../Action.h"

class ActionSwitchToPlay : public Action
{
public:
	ActionSwitchToPlay(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};