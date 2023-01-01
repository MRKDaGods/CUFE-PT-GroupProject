#include "ActionSwitchToPlay.h"
#include "../../Application.h"

ActionSwitchToPlay::ActionSwitchToPlay(Application* app) : Action(app)
{
}

void ActionSwitchToPlay::ReadActionParameters()
{
}

void ActionSwitchToPlay::Execute()
{
	//check for recording
	if (m_Application->GetRecorder()->IsRecording()) {
		m_Frontend->SetStatusBarText("DRAW MODE: Cannot switch to play mode while recording");
		return;
	}

	//switch modes
	m_Application->SetCurrentMode(true);

	//backup graph
	m_Application->GetGraph()->Backup();

	//set status bar msg
	m_Frontend->SetStatusBarText("DRAW MODE: Switched to play mode");
}

ActionType ActionSwitchToPlay::GetActionType()
{
	return ACTION_DRAW_OTHER_PLAY;
}
