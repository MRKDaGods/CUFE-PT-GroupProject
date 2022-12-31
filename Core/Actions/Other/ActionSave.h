#pragma once

#include "../Action.h"

#include <string>

class ActionSave : public Action
{
private:
	std::string m_Filename;

public:
	ActionSave(Application* app, std::string fname = "");

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
	virtual bool CanReadActionParameters() override;
};