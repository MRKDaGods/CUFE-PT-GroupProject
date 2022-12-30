#pragma once

#include "../../DEFS.h"

//we always include Application in our cpp (forward decl) as a result output and input are always included
//therefore add them as forward decls

class Application;
class Output;
class Input;
class UIFrontend;

//Base class for all possible actions
class Action
{
protected:
	Application* m_Application;
	Output* m_Output;
	Input* m_Input;
	UIFrontend* m_Frontend;

public:
	Action(Application* app);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters() abstract;

	//Execute action (code depends on action type)
	virtual void Execute() abstract;

	//Undo the action
	virtual void Undo();

	//Returns the action type
	virtual ActionType GetActionType() abstract;
	
	//Returns true if we can read the params or not
	virtual bool CanReadActionParameters();

	//Returns true if action is of add figure type
	bool IsAddFigureAction();

	//Returns true if action is of change color type
	bool IsChangeColorAction();

	//Returns true if action is of change color mode type
	bool IsChangeColorModeAction();
};