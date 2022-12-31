#include "ActionSound.h"
#include "../../Application.h"

ActionSound::ActionSound(Application* app) : Action(app)
{
}

void ActionSound::ReadActionParameters()
{
}

void ActionSound::Execute()
{
	//set sound state in App, toggle it
	Sound* sound = m_Application->GetSound();
	sound->SetEnabled(!sound->IsEnabled());

	char buf[100];
	sprintf(buf, "SOUND: %s sound", sound->IsEnabled() ? "ENABLED" : "DISABLED");

	//update status bar to reflect the sound state
	m_Frontend->SetStatusBarText(buf);
}

ActionType ActionSound::GetActionType()
{
	return ACTION_DRAW_EXTRA_SOUND;
}
