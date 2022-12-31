#include "ActionStopRecording.h"
#include "../../Recorder.h"
#include "../../Application.h"

ActionStopRecording::ActionStopRecording(Application* app) : Action(app)
{
}

void ActionStopRecording::ReadActionParameters()
{
}

void ActionStopRecording::Execute()
{
	//get recorder and check if we are recording or not
	Recorder* rec = m_Application->GetRecorder();
	if (!rec->IsRecording())
	{
		//we are not recording, display error
		m_Frontend->SetStatusBarText("RECORDING: Recording has not been started");
		return;
	}

	//stop recording
	rec->SetRecording(false);

	//hide rec label
	m_Frontend->SetRecording(false, true);

	//re-draw to hide rec label
	m_Application->Render(true);

	//display message
	m_Frontend->SetStatusBarText("RECORDING: Successfully stopped recording");
}

ActionType ActionStopRecording::GetActionType()
{
	return ACTION_DRAW_OTHER_REC_STOP;
}
