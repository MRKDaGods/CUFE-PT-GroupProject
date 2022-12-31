#pragma once

#include "../Action.h"

class ActionPlayRecording : public Action
{
public:
	ActionPlayRecording(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};

