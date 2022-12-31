#pragma once

#include "Actions/Action.h"

#include <functional>

#define MAX_RECORDING_SZ 20

class Application;

class Recorder
{
private:
	Application* m_Application;

	//The recording buffer
	Action* m_Actions[MAX_RECORDING_SZ];
	int m_ActionCount;

	//Indicates if we are currently recording or not
	bool m_IsRecording;

	//Indicates whether a recording is currently being played
	bool m_IsPlaying;

	//Zeros out the recording buffer and removes the recorded flag from old actions
	void ResetRecordingBuffer();

public:
	Recorder(Application* app);

	//Indicates if we are currently recording or not
	bool IsRecording();

	//Sets the recording state
	void SetRecording(bool rec);

	//Indicates whether a recording is currently being played
	bool IsPlaying();

	//Records an action into the recording buffer
	void RecordAction(Action* action);

	//Returns true if a recording exists (ActionCount > 0)
	bool HasRecording();

	//Plays a recording if exists
	//Callback of return type void and takes in INDEX and COUNT
	void PlayRecording(std::function<void(int, int)> callback = 0);
};