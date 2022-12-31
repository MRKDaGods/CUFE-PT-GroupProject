#include "ActionPlayRecording.h"
#include "../../Application.h"

ActionPlayRecording::ActionPlayRecording(Application* app) : Action(app)
{
}

void ActionPlayRecording::ReadActionParameters()
{
}

void ActionPlayRecording::Execute()
{
	//we cannot play if we are currently recording or no recording exists
	Recorder* rec = m_Application->GetRecorder();
	if (rec->IsRecording())
	{
		m_Frontend->SetStatusBarText("PLAY RECORDING: Stop recording first then play");
		return;
	}

	if (!rec->HasRecording())
	{
		m_Frontend->SetStatusBarText("PLAY RECORDING: No recordings exist");
		return;
	}

	//we have a recording now prepare to play, first of all invoke clear all
	m_Application->HandleAction(ACTION_DRAW_OTHER_CLEAR_ALL);

	//now play recording
	rec->PlayRecording([&](int idx, int count) {
		char buf[100];
		sprintf(buf, "%s P %d/%d", idx % 2 == 0 ? "•" : "", idx + 1, count);

		m_Frontend->SetRecording(true, false, buf);

		//re-draw
		m_Application->Render(true);
	});

	//remove rec label
	m_Frontend->SetRecording(false);

	//update status bar
	m_Frontend->SetStatusBarText("PLAY RECORDING: Done playing recording");

	//re-render
	m_Application->Render(true);
}

ActionType ActionPlayRecording::GetActionType()
{
	return ACTION_DRAW_OTHER_REC_PLAY;
}
