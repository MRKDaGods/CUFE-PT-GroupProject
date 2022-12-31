#include "Recorder.h"
#include "Application.h"

#include <cstring>
#include <sstream>

Recorder::Recorder(Application* app)
{
	m_Application = app;

	//initialize
	m_ActionCount = 0;

	//reset recording buffer
	ResetRecordingBuffer();
	
	//initialially not recording
	SetRecording(false);

	//initially not playing
	m_IsPlaying = false;
}

void Recorder::ResetRecordingBuffer()
{
	//if actions are present, unflag them
	if (m_ActionCount > 0)
	{
		for (int i = 0; i < m_ActionCount; i++)
		{
			//check if not null, as action couldve been deleted in HandleRecordingBuffer
			if (m_Actions[i] != 0)
			{
				m_Actions[i]->SetRecorded(false);
			}
		}
	}

	//zero out recording buffer
	memset(m_Actions, 0, sizeof(Action*) * MAX_RECORDING_SZ);

	m_ActionCount = 0;
}

bool Recorder::IsRecording()
{
	return m_IsRecording;
}

void Recorder::SetRecording(bool rec)
{
	//dont continue if recording state hasnt changed
	if (m_IsRecording == rec) return;

	m_IsRecording = rec;

	//we shouldnt do anything if recording has stopped
	//we MUST clear the action buffer and notify Action history that the buffer has been free'd
	//so old actions could be deleted to prevent memory leaks
	if (m_IsRecording && m_ActionCount > 0)
	{
		//notify action history to delete old unflagged actions
		m_Application->GetActionHistory()->HandleRecordingBuffer(m_Actions, m_ActionCount);

		//free buffer
		ResetRecordingBuffer();
	}
}

bool Recorder::IsPlaying()
{
	return m_IsPlaying;
}

void Recorder::RecordAction(Action* action)
{
	//dont do anything if not recording
	if (!m_IsRecording) return;

	//check if action is recordable
	//all draw mode actions are recordable except for start/stop recording, play recording, save graph, load graph, switch and exit
	switch (action->GetActionType())
	{
	case ACTION_DRAW_OTHER_REC_START:
	case ACTION_DRAW_OTHER_REC_STOP:
	case ACTION_DRAW_OTHER_REC_PLAY:
	case ACTION_DRAW_OTHER_SAVE_GRAPH:
	case ACTION_DRAW_OTHER_OPEN_GRAPH:
	case ACTION_DRAW_OTHER_PLAY:
	case ACTION_DRAW_OTHER_EXIT:
		return;

	//we can use all other actions
	//we are not checking against play mode actions as m_IsRecording would always be false inside PlayMode
	default:
		break;
	}

	//action needs to be marked as recorded to prevent it from being
	//deleted by ActionHistory

	//mark recorded
	action->SetRecorded(true);

	//store in buffer
	m_Actions[m_ActionCount++] = action;

	m_Application->DebugLog([&](DEBUG_LOG_PARAM) {
		stream << "Recorded new action type = " << action->GetActionType()
			<< "\nRec Action count = " << m_ActionCount << '\n';
	});

	//we have reached the max sz of operations
	if (m_ActionCount == MAX_RECORDING_SZ)
	{
		//stop recording
		//SetRecording(false);

		//invoke the stop recording action instead from application
		m_Application->HandleAction(ACTION_DRAW_OTHER_REC_STOP);
	}
}

bool Recorder::HasRecording()
{
	//true if atleast 1 action exists
	return m_ActionCount > 0;
}

void Recorder::PlayRecording(std::function<void(int, int)> callback)
{
	//check if recording exists and we are not currently recording
	if (!HasRecording() || m_IsRecording) return;

	//mark playing
	//no interactions should be allowed until the playing ends
	m_IsPlaying = true;

	//start playing !!!
	for (int i = 0; i < m_ActionCount; i++)
	{
		//execute the action
		m_Actions[i]->Execute();

		//add history
		m_Application->GetActionHistory()->AddAction(m_Actions[i]);

		//TODO: update arguments or automate clicks for action arguments

		if (callback != 0)
		{
			callback(i, m_ActionCount);
		}

		//sleep for 1 sec
		Sleep(1000);
	}

	//recording ended, remove flag
	m_IsPlaying = false;

	//TODO: prevent interactions while playings
}
