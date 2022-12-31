#pragma once

#include "../Action.h"

class ActionStartRecording : public Action
{
public:
	ActionStartRecording(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};

