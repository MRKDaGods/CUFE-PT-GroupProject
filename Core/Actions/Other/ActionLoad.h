#pragma once

#include "../Action.h"

#include <string>

class ActionLoad : public Action
{
private:
	std::string m_Filename;

public:
	ActionLoad(Application* app, std::string fname = "");

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
	virtual bool CanReadActionParameters() override;
};