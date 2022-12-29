#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

//Add Square Action class
class ActionAddSquare : public Action
{
private:
	Point m_Center;

public:
	ActionAddSquare(Application* app);

	//Reads rectangle parameters
	virtual void ReadActionParameters() override;

	//Add rectangle to the ApplicationManager
	virtual void Execute() override;
};