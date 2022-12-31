#include "Application.h"

#include "Actions/Colors/ActionSetColor.h"
#include "Actions/Colors/ActionSetColorMode.h"

#include "Actions/Extra/ActionSound.h"
#include "Actions/Extra/ActionDrag.h"
#include "Actions/Extra/ActionResize.h"

#include "Actions/Other/ActionSelect.h"
#include "Actions/Other/ActionMove.h"
#include "Actions/Other/ActionDelete.h"
#include "Actions/Other/ActionClearAll.h"
#include "Actions/Other/ActionSave.h"
#include "Actions/Other/ActionLoad.h"
#include "Actions/Other/ActionStartRecording.h"
#include "Actions/Other/ActionStopRecording.h"
#include "Actions/Other/ActionPlayRecording.h"
#include "Actions/Other/ActionUndo.h"
#include "Actions/Other/ActionRedo.h"
#include "Actions/Other/ActionSwitchToPlay.h"
#include "Actions/Other/ActionExit.h"

#include "Actions/Play/ActionPickAndHide.h"
#include "Actions/Play/ActionSwitchToDraw.h"

#include "Actions/Shapes/ActionAddRectangle.h"
#include "Actions/Shapes/ActionAddSquare.h"
#include "Actions/Shapes/ActionAddTriangle.h"
#include "Actions/Shapes/ActionAddHexagon.h"
#include "Actions/Shapes/ActionAddCircle.h"

#include "../Utils/Color.h"
#include "Serializer.h"

#include <map>
#include <iostream>
#include <sstream>
#include <set>
#include <vector>

//Action function pointer
#define _ACT_FNPTR(actClass) [](Application* app) -> Action* { return new actClass(app); }
#define _ACT_FNPTR_COL(col) [](Application* app) -> Action* { return new ActionSetColor(app, col); }
#define _ACT_FNPTR_COLMODE(mode) [](Application* app) -> Action* { return new ActionSetColorMode(app, mode); }
#define _ACT_FNPTR_PICKANDHIDE(mode) [](Application* app) -> Action* { return new ActionPickAndHide(app, mode); }

//ActionType to function pointer that returns a new instance of the action
std::map<ActionType, ActionInstantiator> actionDataTable2 {
	//////////////////////////////////////////////
	//Shape actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_SHAPE_RECTANGLE, _ACT_FNPTR(ActionAddRectangle) },
	{ ACTION_DRAW_SHAPE_SQUARE, _ACT_FNPTR(ActionAddSquare) },
	{ ACTION_DRAW_SHAPE_TRIANGLE, _ACT_FNPTR(ActionAddTriangle) },
	{ ACTION_DRAW_SHAPE_HEXAGON, _ACT_FNPTR(ActionAddHexagon) },
	{ ACTION_DRAW_SHAPE_CIRCLE, _ACT_FNPTR(ActionAddCircle) },

	//////////////////////////////////////////////
	//Color actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_COL_BLACK, _ACT_FNPTR_COL(DWCOLOR_BLACK) },
	{ ACTION_DRAW_COL_YELLOW, _ACT_FNPTR_COL(DWCOLOR_YELLOW) },
	{ ACTION_DRAW_COL_ORANGE, _ACT_FNPTR_COL(DWCOLOR_ORANGE) },
	{ ACTION_DRAW_COL_RED, _ACT_FNPTR_COL(DWCOLOR_RED) },
	{ ACTION_DRAW_COL_GREEN, _ACT_FNPTR_COL(DWCOLOR_GREEN) },
	{ ACTION_DRAW_COL_BLUE, _ACT_FNPTR_COL(DWCOLOR_BLUE) },

	//////////////////////////////////////////////
	//ColorMode actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_COLMODE_FILL, _ACT_FNPTR_COLMODE(DWCOLORMODE_FILL) },
	{ ACTION_DRAW_COLMODE_DRAW, _ACT_FNPTR_COLMODE(DWCOLORMODE_DRAW) },

	//////////////////////////////////////////////
	//Other actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_OTHER_SELECT, _ACT_FNPTR(ActionSelect) },
	{ ACTION_DRAW_OTHER_MOVE, _ACT_FNPTR(ActionMove) },
	{ ACTION_DRAW_OTHER_DELETE_FIG, _ACT_FNPTR(ActionDelete) },
	{ ACTION_DRAW_OTHER_CLEAR_ALL, _ACT_FNPTR(ActionClearAll) },
	{ ACTION_DRAW_OTHER_SAVE_GRAPH, _ACT_FNPTR(ActionSave) },
	{ ACTION_DRAW_OTHER_OPEN_GRAPH, _ACT_FNPTR(ActionLoad) },
	{ ACTION_DRAW_OTHER_REC_START, _ACT_FNPTR(ActionStartRecording) },
	{ ACTION_DRAW_OTHER_REC_STOP, _ACT_FNPTR(ActionStopRecording) },
	{ ACTION_DRAW_OTHER_REC_PLAY, _ACT_FNPTR(ActionPlayRecording) },
	{ ACTION_DRAW_OTHER_UNDO, _ACT_FNPTR(ActionUndo) },
	{ ACTION_DRAW_OTHER_REDO, _ACT_FNPTR(ActionRedo) },
	{ ACTION_DRAW_OTHER_PLAY, _ACT_FNPTR(ActionSwitchToPlay) },
	{ ACTION_DRAW_OTHER_EXIT, _ACT_FNPTR(ActionExit) },

	//////////////////////////////////////////////
	//Play mode actions
	//////////////////////////////////////////////
	{ ACTION_PLAY_PICKHIDE_FIGTYPE, _ACT_FNPTR_PICKANDHIDE(PMPICKHIDE_FIG_TYPE) },
	{ ACTION_PLAY_PICKHIDE_FIGCOL, _ACT_FNPTR_PICKANDHIDE(PMPICKHIDE_FIG_COL) },
	{ ACTION_PLAY_PICKHIDE_FIGTYPE_COL, _ACT_FNPTR_PICKANDHIDE(PMPICKHIDE_FIG_TYPE_COL) },
	{ ACTION_PLAY_OTHER_DRAW, _ACT_FNPTR(ActionSwitchToDraw) },

	//////////////////////////////////////////////
	//Extra actions (bonus)
	//////////////////////////////////////////////
	{ ACTION_DRAW_EXTRA_SOUND, _ACT_FNPTR(ActionSound) },
	{ ACTION_DRAW_EXTRA_DRAG, _ACT_FNPTR(ActionDrag) },
	{ ACTION_DRAW_EXTRA_RESIZE, _ACT_FNPTR(ActionResize) },
};

std::map<ActionType, ActionData*> actionDataTable {
	//////////////////////////////////////////////
	//Shape actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_SHAPE_RECTANGLE, action_draw_shape_rectangle },
	{ ACTION_DRAW_SHAPE_SQUARE, action_draw_shape_square },
	{ ACTION_DRAW_SHAPE_TRIANGLE, action_draw_shape_triangle },
	{ ACTION_DRAW_SHAPE_HEXAGON, action_draw_shape_hexagon },
	{ ACTION_DRAW_SHAPE_CIRCLE, action_draw_shape_circle },

	//////////////////////////////////////////////
	//Color actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_COL_BLACK, action_draw_col_black },
	{ ACTION_DRAW_COL_YELLOW, action_draw_col_yellow },
	{ ACTION_DRAW_COL_ORANGE, action_draw_col_orange },
	{ ACTION_DRAW_COL_RED, action_draw_col_red },
	{ ACTION_DRAW_COL_GREEN, action_draw_col_green },
	{ ACTION_DRAW_COL_BLUE, action_draw_col_blue },

	//////////////////////////////////////////////
	//ColorMode actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_COLMODE_FILL, action_draw_colmode_fill },
	{ ACTION_DRAW_COLMODE_DRAW, action_draw_colmode_draw },

	//////////////////////////////////////////////
	//Other actions
	//////////////////////////////////////////////
	{ ACTION_DRAW_OTHER_SELECT, action_draw_other_select },
	{ ACTION_DRAW_OTHER_MOVE, action_draw_other_move },
	{ ACTION_DRAW_OTHER_DELETE_FIG, action_draw_other_delete_fig },
	{ ACTION_DRAW_OTHER_CLEAR_ALL, action_draw_other_clear_all },
	{ ACTION_DRAW_OTHER_SAVE_GRAPH, action_draw_other_save_graph },
	{ ACTION_DRAW_OTHER_OPEN_GRAPH, action_draw_other_open_graph },
	{ ACTION_DRAW_OTHER_REC_START, action_draw_other_rec_start },
	{ ACTION_DRAW_OTHER_REC_STOP, action_draw_other_rec_stop },
	{ ACTION_DRAW_OTHER_REC_PLAY, action_draw_other_rec_pause },
	{ ACTION_DRAW_OTHER_UNDO, action_draw_other_undo },
	{ ACTION_DRAW_OTHER_REDO, action_draw_other_redo },
	{ ACTION_DRAW_OTHER_PLAY, action_draw_other_play },
	{ ACTION_DRAW_OTHER_EXIT, action_draw_other_exit },

	//////////////////////////////////////////////
	//Play mode actions
	//////////////////////////////////////////////
	{ ACTION_PLAY_PICKHIDE_FIGTYPE, action_play_pickhide_figtype },
	{ ACTION_PLAY_PICKHIDE_FIGCOL, action_play_pickhide_figcol },
	{ ACTION_PLAY_PICKHIDE_FIGTYPE_COL, action_play_pickhide_figtype_col },
	{ ACTION_PLAY_OTHER_DRAW, action_play_other_draw }
};

void Application::Print(string msg) const
{
	m_Frontend->SetStatusBarText(msg);
}

ActionInstantiator Application::GetActionInstantiatorFromType(const ActionType& type)
{
	auto it = actionDataTable2.find(type);
	return it != actionDataTable2.end() ? it->second : 0;
}

Application::Application()
{
	//create IO
	m_Output = new Output(this);
	m_Input = m_Output->CreateInput();

	//defaults
	SetCurrentColor(DWCOLOR_BLACK);
	SetCurrentColorMode(DWCOLORMODE_DRAW);

	//set running
	m_IsRunning = true;

	//add the initial gfx info to the stack
	m_GfxStack.push(GfxInfo());

	//set initial gfx info
	SetGfxInfo();

	//create frontend
	m_Frontend = new UIFrontend(this);

	//initialize selected figure
	m_SelectedFigure = 0;

	//initialize figure count
	m_FigureCount = 0;

	//zero out the figure pointers
	memset(m_FigureList, 0, sizeof(CFigure*) * MAX_FIGURE_COUNT);

	//initialize action history
	m_ActionHistory = new ActionHistory(this);

	//initialize recorder
	m_Recorder = new Recorder(this);

	//initialize graph
	m_Graph = new Graph(this);

	//initialize sound
	m_Sound = new Sound();

	//init rand
	srand(time(0));
}

Application::~Application()
{
	delete m_Output;
	delete m_Input;
	delete m_Frontend;
	delete m_ActionHistory;
	delete m_Recorder;
	delete m_Graph;
	delete m_Sound;

	//delete action data as well
	for (auto &x : actionDataTable)
	{
		delete x.second;
	}
}

bool Application::IsRunning() const
{
	return m_IsRunning;
}

void Application::Render(bool clearDrawArea, bool renderFrontend)
{
	if (clearDrawArea)
	{
		m_Output->ClearDrawArea();
	}

	for (int i = 0; i < m_FigureCount; i++)
	{
		if (m_FigureList[i])
		{
			m_FigureList[i]->Draw(m_Output);
		}
	}

	if (renderFrontend)
	{
		//frontend should be the top most
		m_Frontend->Render();
	}
}

void Application::Loop()
{
	Point mousePos = m_Input->GetMousePos();

	if (m_LastMousePosition.x == 0 && m_LastMousePosition.y == 0)
	{
		m_LastMousePosition = mousePos;
	}

	int m0 = 0;
	bool mouseDown = m_Input->GetMouseDown();

	if (mouseDown)
	{
		if (!m_MouseDown)
		{
			m_MouseDown = true;

			//send mdown event
			UITouchEvent evt(mousePos.x, mousePos.y, UITouchEventType::Down);
			m_Frontend->HandleTouchEvent(&evt);
		}
	}
	else if (m_MouseDown)
	{
		m_MouseDown = false;

		//send mup event
		UITouchEvent evt(mousePos.x, mousePos.y, UITouchEventType::Up);
		m_Frontend->HandleTouchEvent(&evt);
	}

	if (mousePos.x != m_LastMousePosition.x || mousePos.y != m_LastMousePosition.y)
	{
		//send mdrag event
		UITouchEvent evt(mousePos.x, mousePos.y, UITouchEventType::Drag);
		m_Frontend->HandleTouchEvent(&evt);
	}

	//get current action
	/*ActionType action = m_Input->GetUserAction();

	DebugLog([action](DEBUG_LOG_PARAM) {
		stream << "Handling action: " << action << endl;
	});

	//check if action is a draw mode action
	if (IsDrawModeAction(action))
	{
		HandleDrawModeAction(action);
	}

	//manually handle other actions
	//handle the action
	switch (action)
	{
	case EXIT:
		Exit();
		break;

	default:
		break;
	}*/
}

void Application::SetGfxInfo(color drawColor, int borderWidth, bool fill, color fillColor, int fixedRadius)
{
	//set graphic info
	GfxInfo* gfx = GetGfxInfo();
	gfx->draw_col = drawColor;
	gfx->border_width = borderWidth;
	gfx->is_filled = fill;
	gfx->fill_col = fillColor;
	gfx->fixed_radius = fixedRadius;
}

GfxInfo* Application::GetGfxInfo()
{
	return &m_GfxStack.top();
}

void Application::PushGfxInfo(const GfxInfo& gfxInfo)
{
	m_GfxStack.push(gfxInfo);
}

void Application::PopGfxInfo()
{
	m_GfxStack.pop();
}

void Application::DebugLog(string msg, bool appendNewLine)
{
#ifdef ENABLE_DEBUG_LOG
	cout << "[DEBUG] " << msg;

	if (appendNewLine)
	{
		cout << endl;
	}
#endif
}

void Application::DebugLog(function<void(DEBUG_LOG_PARAM)> log)
{
	//create a string stream, log to it, then print to console
	stringstream stream;
	log(stream);

	DebugLog(stream.str(), false);
}

Output* Application::GetOutput()
{
	return m_Output;
}

Input* Application::GetInput()
{
	return m_Input;
}

UIFrontend* Application::GetUIFrontend()
{
	return m_Frontend;
}

void Application::HandleAction(const ActionType& type)
{
	DebugLog("Handling action...");

	//find action instantiator from type
	ActionInstantiator instantiator = GetActionInstantiatorFromType(type);
	if (instantiator)
	{
		//call instantiator and create action
		auto action = instantiator(this);

		//if sound is enabled, play the sound
		if (m_Sound->IsEnabled())
		{
			m_Sound->PlaySound(type);
		}

		//read params externally
		if (action->CanReadActionParameters())
		{
			action->ReadActionParameters();
		}

		//execute action
		action->Execute();

		//action history should delete the last executed action incase it was an unsupported one
		//no memory leaks :)
		m_ActionHistory->AddAction(action);

		//if recording, add to recorder
		if (m_Recorder->IsRecording())
		{
			m_Recorder->RecordAction(action);
		}

		//output action history debug
		DebugLog(
			[&](DEBUG_LOG_PARAM) {
				stream << "ACTIONS: [ ";
				auto acts = m_ActionHistory->GetHistory();
				for (int i = 0; i < acts->GetCount(); i++)
				{
					stream << (*acts)[i]->GetActionType() << " ";
				}

				stream << "]\n";

				auto next = acts->PeekNext();
				if (next != 0)
				{
					stream << "NEXT = " << next->GetActionType() << '\n';
				}
			}
		);
	}
}

void Application::Exit()
{
	DebugLog("Exiting the app");

	m_IsRunning = false;
}

DWColorModes Application::GetCurrentColorMode()
{
	return m_CurrentColorMode;
}

void Application::SetCurrentColorMode(DWColorModes colMode)
{
	m_CurrentColorMode = colMode;
}

DWColors Application::GetCurrentColor()
{
	return m_CurrentColor;
}

void Application::SetCurrentColor(DWColors color)
{
	m_CurrentColor = color;
}

void Application::SetCurrentMode(bool isPlayMode)
{
	m_Frontend->SetCurrentMode(isPlayMode);
}

void Application::AddFigure(CFigure* pFig, bool clearDrawArea, bool shouldRender)
{
	if (m_FigureCount < MAX_FIGURE_COUNT) 
	{
		m_FigureList[m_FigureCount++] = pFig;

		//so by default AddFigure calls Render
		//should we let the Action class responsible for the dirty handling?
		if (shouldRender)
		{
			Render(clearDrawArea);
		}
	}
}

void Application::DeleteFigure(CFigure* fig, bool deletePtr)
{
	//dont continue if fig is null
	if (fig == 0) return;

	//find fig in fig list, if found, delete it, shift elements then re-render

	int figIdx = -1;
	for (int i = 0; i < m_FigureCount; i++)
	{
		if (m_FigureList[i] == fig)
		{
			//we found the figure
			//delete it
			if (deletePtr)
			{
				delete m_FigureList[i];
			}

			//zero out the location
			m_FigureList[i] = 0;

			figIdx = i;
			break;
		}
	}

	if (figIdx == -1) return; //figure not found

	//if the removed figure wasnt the last figure in the array, shift
	// |||||_|     ->    ||||||_
	//      ^                  ^

	if (figIdx < m_FigureCount - 1)
	{
		//not the last element, so shift to the left
		for (int i = figIdx + 1; i < m_FigureCount; i++)
		{
			m_FigureList[i - 1] = m_FigureList[i];
		}

		//zero out the location of the last element
		m_FigureList[m_FigureCount - 1] = 0;
	}

	//decrement figure count
	m_FigureCount--;
}

void Application::DeleteAllFigures()
{
	//dont do anything if there are no figures
	if (m_FigureCount == 0) return;

	for (int i = 0; i < m_FigureCount; i++)
	{
		//delete it
		delete m_FigureList[i];

		//zero out the location
		m_FigureList[i] = 0;
	}

	//set figure count to 0
	m_FigureCount = 0;
}

CFigure* Application::GetFigure(int x, int y) const
{
	//find the first figure that satisfies the hit test
	for (int i = 0; i < m_FigureCount; i++)
	{
		if (m_FigureList[i]->HitTest(Point{ x, y }))
		{
			return m_FigureList[i];
		}
	}

	return 0;
}

bool Application::ContainsFigure(CFigure* fig)
{
	for (int i = 0; i < m_FigureCount; i++)
	{
		if (m_FigureList[i] == fig)
		{
			return true;
		}
	}

	return false;
}

CFigure* Application::GetSelectedFigure()
{
	return m_SelectedFigure;
}

void Application::SetSelectedFigure(CFigure* fig)
{
	m_SelectedFigure = fig;
}

ActionHistory* Application::GetActionHistory()
{
	return m_ActionHistory;
}

int Application::GetFigureCount()
{
	return m_FigureCount;
}

void Application::SaveAll(Serializer* serializer)
{	 
	//save all figures
	for (int i = 0; i < m_FigureCount; i++)
	{
		m_FigureList[i]->Save(serializer);
	}
}

Recorder* Application::GetRecorder()
{
	return m_Recorder;
}

Graph* Application::GetGraph()
{
	return m_Graph;
}

bool operator<(const color& c1, const color& c2)
{
	return c1.ucRed < c2.ucRed;
}

void Application::GetDistinctFiguresInfo(std::vector<color>* colors, std::vector<DWShape>* shapes)
{
	//find colors and shapes
	//implement first using a set
	std::set<color> cols;
	std::set<DWShape> shps;

	for (int i = 0; i < m_FigureCount; i++)
	{
		CFigure* fig = m_FigureList[i];

		if (colors != 0)
		{
			cols.insert(fig->GetGfxInfo()->fill_col);
		}

		if (shapes != 0)
		{
			shps.insert(fig->GetShape());
		}
	}

	//after adding to a set, we ensure that they contain unique elements
	//initialize arrays
	//store in a vector to put them in contiguous memory
	//and then copy to pointer array
	if (colors != 0)
	{
		*colors = std::vector<color>(cols.begin(), cols.end());
	}

	if (shapes != 0)
	{
		*shapes = std::vector<DWShape>(shps.begin(), shps.end());
	}
}

int Application::GetFigureCountWithShape(DWShape shape)
{
	int c = 0;
	for (int i = 0; i < m_FigureCount; i++)
	{
		if (m_FigureList[i]->GetShape() == shape) c++;
	}

	return c;
}

int Application::GetFigureCountWithColor(color col)
{
	int c = 0;
	for (int i = 0; i < m_FigureCount; i++)
	{
		if (m_FigureList[i]->GetGfxInfo()->fill_col == col) c++;
	}

	return c;
}

int Application::GetFigureCountWithShapeAndColor(DWShape shape, color col)
{
	int c = 0;
	for (int i = 0; i < m_FigureCount; i++)
	{
		if (m_FigureList[i]->GetShape() == shape && m_FigureList[i]->GetGfxInfo()->fill_col == col) c++;
	}

	return c;
}

color Application::GetRandomColorForShape(DWShape shape)
{
	//store in a set to attain uniqueness
	std::set<color> cols;

	for (int i = 0; i < m_FigureCount; i++)
	{
		if (m_FigureList[i]->GetShape() == shape)
		{
			cols.insert(m_FigureList[i]->GetGfxInfo()->fill_col);
		}
	}

	//return a random element from the set
	return *std::next(cols.begin(), rand() % cols.size());
}

Sound* Application::GetSound()
{
	return m_Sound;
}
