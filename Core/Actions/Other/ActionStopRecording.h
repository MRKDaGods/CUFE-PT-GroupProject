#pragma once

#include "../Action.h"

class ActionStopRecording : public Action
{
public:
	ActionStopRecording(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};

