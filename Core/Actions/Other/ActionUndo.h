#pragma once

#include "../Action.h"

class ActionUndo : public Action
{
public:
	ActionUndo(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};