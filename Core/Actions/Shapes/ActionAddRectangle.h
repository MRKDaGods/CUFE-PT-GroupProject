#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

//Add Rectangle Action class
class ActionAddRectangle : public Action
{
private:
	//Rectangle Corners
	Point m_P1;
	Point m_P2;

public:
	ActionAddRectangle(Application* app);

	//Reads rectangle parameters
	virtual void ReadActionParameters() override;

	//Add rectangle to the ApplicationManager
	virtual void Execute() override;
};