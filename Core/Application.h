#pragma once

#include <functional>
#include <stack>
#include <vector>
#include <map>

#include "../GUI/Frontend/UIFrontend.h"
#include "../GUI/Output.h"
#include "../GUI/Input.h"
#include "../Common.h"
#include "../Figures/CFigure.h"
#include "Actions/Action.h"
#include "ActionHistory.h"
#include "Recorder.h"
#include "Graph.h"
#include "Sound.h"

#define DEBUG_LOG_PARAM std::stringstream& stream
#define MAX_FIGURE_COUNT 200

typedef Action*(*ActionInstantiator)(Application*);

class Application
{
private:
	//Output interface
	Output* m_Output;

	//Input interface
	Input* m_Input;

	//Is the application running?
	bool m_IsRunning;

	//ActionType to function pointer that returns a new instance of the action
	std::map<ActionType, ActionInstantiator> m_ActionTable;

	//Figure graphical information
	std::stack<GfxInfo> m_GfxStack;

	//The interface frontend, responsible for top level rendering
	UIFrontend* m_Frontend;

	bool m_MouseDown;
	Point m_LastMousePosition;

	//The current color mode
	DWColorModes m_CurrentColorMode;

	//The current color
	DWColors m_CurrentColor;

	//Actual number of figures
	int m_FigureCount;

	//List of all figures
	CFigure* m_FigureList[MAX_FIGURE_COUNT];

	//Pointer to the selected figure
	CFigure* m_SelectedFigure;

	//Handles the action history
	ActionHistory* m_ActionHistory;

	//Handles the recording
	Recorder* m_Recorder;

	//Responsible for the graph data
	Graph* m_Graph;

	//Responsible for playing sound
	Sound* m_Sound;

	//Base global id
	int m_GlobalID;

	//Prints a message to the status bar
	void Print(string msg) const;

	//Initializes the action table and adds all action handlers to the table
	void InitActionTable();

	//Returns an action instantiator from type, null if not found
	ActionInstantiator GetActionInstantiatorFromType(const ActionType& type);

public:
	Application();
	~Application();

	//Indicates whether the app is running or not
	bool IsRunning() const;

	//Manually requests the frontend to render
	void Render(bool clearDrawArea = false, bool renderFrontend = true);

	//App main loop
	void Loop();

	//Sets the graphical info to use
	void SetGfxInfo(color drawColor = BLACK, int borderWidth = 5, bool fill = false, color fillColor = BLACK, int fixedRadius = 50);

	//Returns the gfx info at the top of the stack
	GfxInfo* GetGfxInfo();

	void PushGfxInfo(const GfxInfo& gfxInfo);

	void PopGfxInfo();

	//Logs a debug message to the console
	void DebugLog(string msg, bool appendNewLine = true);

	//Logs a debug message stream to the console
	void DebugLog(function<void(DEBUG_LOG_PARAM)> log);

	//Returns a pointer to Output
	Output* GetOutput();

	//Returns a pointer to Input
	Input* GetInput();

	//Returns a pointer to UIFrontend
	UIFrontend* GetUIFrontend();

	//Handles an action of ActionType type
	void HandleAction(const ActionType& type, bool silent = false);

	//Terminates the app
	void Exit();

	DWColorModes GetCurrentColorMode();
	void SetCurrentColorMode(DWColorModes colMode);

	DWColors GetCurrentColor();
	void SetCurrentColor(DWColors color);

	//Sets the current mode, false = DrawMode, true = PlayMode
	void SetCurrentMode(bool isPlayMode);

	//Adds a new figure to the FigList
	void AddFigure(CFigure* pFig, bool clearDrawArea = false, bool shouldRender = true);

	//Removes a figure if exists
	//deletePtr if true, the underlying pointer will be deleted
	void DeleteFigure(CFigure* fig, bool deletePtr = true);

	//Deletes all figures if any
	void DeleteAllFigures();

	//Search for a figure given a point inside the figure
	CFigure* GetFigure(int x, int y) const;

	//Searches for a figure with a specific ID
	CFigure* GetFigureWithID(int id);

	//Returns true if a figure exists
	bool ContainsFigure(CFigure* fig);

	//Returns a pointer to the currently selected figure
	CFigure* GetSelectedFigure();
	
	//Sets the currently selected figure
	void SetSelectedFigure(CFigure* fig);

	//Returns the action history
	ActionHistory* GetActionHistory();

	//Returns the number of figures
	int GetFigureCount();

	//Saves all figures to serializer
	void SaveAll(Serializer* serializer);

	//Returns the recorder
	Recorder* GetRecorder();

	//Returns a pointer to the graph
	Graph* GetGraph();

	//Gets distinct info of figures (colors/type) and passes them back using pointers
	void GetDistinctFiguresInfo(std::vector<color>* colors, std::vector<DWShape>* shapes);

	//Gets the number of figures with the specified shape
	int GetFigureCountWithShape(DWShape shape);

	//Gets the number of figures with the specified color
	int GetFigureCountWithColor(color col);

	//Gets the number of figures with the specified shape and color
	int GetFigureCountWithShapeAndColor(DWShape shape, color col);

	//Returns a random color of an existing figure with specified shape
	color GetRandomColorForShape(DWShape shape);

	//Returns a pointer to a sound
	Sound* GetSound();

	//Returns a new unique ID for a shape
	int AllocateFigureID();

	//Resets the global ID
	void ResetGlobalID();
};