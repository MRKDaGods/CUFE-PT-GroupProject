#pragma once

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
};