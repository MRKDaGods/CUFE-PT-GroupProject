#pragma once

#include "../Action.h"

class ActionExit : public Action
{
public:
	ActionExit(Application* app);

	//Reads rectangle parameters
	virtual void ReadActionParameters() override;

	//Add rectangle to the ApplicationManager
	virtual void Execute() override;

};