#pragma once

#include "../DEFS.h"

#include <string>
#include <map>

//remove PlaySound macro from Windows.h
#undef PlaySound

class Sound
{
private:
	//Indicates whether sound is enabled or not
	bool m_Enabled;

	//Map storing action type to sound path
	std::map<ActionType, std::string> m_Sounds;

	//Registers a sound to the map given its action type and path
	void RegisterSound(ActionType type, std::string path);

public:
	Sound();

	//Sets the enabled state of the sound
	void SetEnabled(bool enable);

	//Indicates whether sound is enabled or not
	bool IsEnabled();

	//Plays a sound for an action type
	void PlaySound(const ActionType& type);
};