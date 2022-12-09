#pragma once

#include <functional>

#include "../GUI/Frontend/UIFrontend.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
#include "ActionData.h"
#include "../Common.h"

#define DEBUG_LOG_PARAM std::stringstream& stream

class Application
{
private:
	//Output interface
	Output* m_Output;

	//Input interface
	Input* m_Input;

	//Is the application running?
	bool m_IsRunning;

	//Figure graphical information
	GfxInfo m_GfxInfo;

	//The interface frontend, responsible for top level rendering
	UIFrontend* m_Frontend;

	bool m_MouseDown;
	Point m_LastMousePosition;

	//The current color mode
	DWColorModes m_CurrentColorMode;

	//Prints a message to the status bar
	void Print(string msg) const;

	//Determines whether the given action is a draw mode action or not
	bool IsDrawModeAction(const ActionType& action) const;

	//Handles an action related to draw mode
	void HandleDrawModeAction(const ActionType& action);

	//Returns an action data from type, null if not found
	ActionData* GetActionDataFromType(ActionType type);

public:
	Application();
	~Application();

	//Indicates whether the app is running or not
	bool IsRunning() const;

	//Manually requests the frontend to render
	void Render();

	//App main loop
	void Loop();

	//Sets the graphical info to use
	void SetGfxInfo(color drawColor = BLACK, int borderWidth = 5, bool fill = false, color fillColor = BLACK, int fixedRadius = 50);

	//Returns the gfx info
	GfxInfo* GetGfxInfo();

	//Logs a debug message to the console
	void DebugLog(string msg, bool appendNewLine = true);

	//Logs a debug message stream to the console
	void DebugLog(function<void(DEBUG_LOG_PARAM)> log);

	//Returns a pointer to Output
	Output* GetOutput();

	//Returns a pointer to Input
	Input* GetInput();

	//Handles an action of ActionType type
	void HandleAction(const ActionType& type);

	//Terminates the app
	void Exit();

	DWColorModes GetCurrentColorMode();
	void SetCurrentColorMode(DWColorModes colMode);

	//Sets the current color with respect to the selected color mode (fill/draw)
	void SetDrawModeColor(DWColors color);

	//Sets the current mode, false = DrawMode, true = PlayMode
	void SetCurrentMode(bool isPlayMode);
};