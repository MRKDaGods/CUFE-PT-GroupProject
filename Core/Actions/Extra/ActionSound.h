#pragma once

#include "../Action.h"

class ActionSound : public Action
{
public:
	ActionSound(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};