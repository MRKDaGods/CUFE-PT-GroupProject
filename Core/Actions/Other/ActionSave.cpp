#include "ActionSave.h"
#include "../../Application.h"
#include "../../Serializer.h"

ActionSave::ActionSave(Application* app) : Action(app)
{
	m_Filename = "";
}

void ActionSave::ReadActionParameters()
{
	m_Frontend->SetStatusBarText("SAVE: Enter filename");

	//get filename
	m_Filename = m_Input->GetString(m_Output);

	m_Frontend->SetStatusBarText("");
}

void ActionSave::Execute()
{
	//create serializer
	Serializer s(m_Filename);

	//write current properties
	//current draw color
	GfxInfo* gfx = m_Application->GetGfxInfo();
	s.WriteColor(NativeToFrontendColor(gfx->draw_col));

	//current fill color
	s.WriteColor(NativeToFrontendColor(gfx->fill_col));

	//figure count
	s.Write(m_Application->GetFigureCount());

	//write figure data
	m_Application->SaveAll(&s);

	//close serializer
	s.Close();

	m_Frontend->SetStatusBarText("SAVE: Saved graph to " + m_Filename);
}

ActionType ActionSave::GetActionType()
{
	return ACTION_DRAW_OTHER_SAVE_GRAPH;
}
