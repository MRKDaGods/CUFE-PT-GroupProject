#pragma once

#include "../Action.h"

#include <string>

class ActionLoad : public Action
{
private:
	std::string m_Filename;

public:
	ActionLoad(Application* app);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};