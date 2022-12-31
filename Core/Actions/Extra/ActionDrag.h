#pragma once

#include "../Action.h"

class ActionDrag : public Action
{
private:
	Point m_InitialPoint;
	bool m_Down;

public:
	ActionDrag(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
	virtual bool CanReadActionParameters() override;
};