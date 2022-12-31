#pragma once

#include "../Action.h"

class ActionResize : public Action
{
private:
	Point m_InitialPoint;
	bool m_Down;

public:
	ActionResize(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
	virtual bool CanReadActionParameters() override;
};