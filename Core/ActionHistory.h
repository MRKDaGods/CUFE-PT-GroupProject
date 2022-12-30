#pragma once

#include <stack>

#include "Actions/Action.h"
#include "../Utils/CircularBuffer.hpp"

class Application;

class ActionHistory
{
private:
	Application* m_Application;

	//A circular buffer containing a max of 5 actions
	CircularBuffer<Action*, 5>* m_Actions;

	//The last executed action regardless of anything else
	Action* m_LastAction;

	//Returns true if an action is supported by the undo/redo operation
	bool IsActionSupported(Action* action);

	//Cleanup event handler for the actions circular buffer
	static void OnActionRemoved(Action** action);

public:
	ActionHistory(Application* app);
	~ActionHistory();

	//Adds an action to the history
	//Returns true if the action was successfully added
	bool AddAction(Action* action);

	//Clears the history
	void Clear();

	CircularBuffer<Action*, 5>* GetHistory();
	Action* GetLastAction();
};

