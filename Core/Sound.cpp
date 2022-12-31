#include "Sound.h"

Sound::Sound()
{
	//Initially disabled
	m_Enabled = false;

	//empty sound map
	m_Sounds = { };

	//register all sounds
	RegisterSound(ACTION_DRAW_SHAPE_CIRCLE, "sounds\\circle.wav");
	RegisterSound(ACTION_DRAW_SHAPE_HEXAGON, "sounds\\hexagon.wav");
	RegisterSound(ACTION_DRAW_SHAPE_RECTANGLE, "sounds\\rectangle.wav");
	RegisterSound(ACTION_DRAW_SHAPE_SQUARE, "sounds\\square.wav");
	RegisterSound(ACTION_DRAW_SHAPE_TRIANGLE, "sounds\\triangle.wav");
}

void Sound::RegisterSound(ActionType type, std::string path)
{
	//add to map
	m_Sounds.insert({ type, path });
}

void Sound::SetEnabled(bool enable)
{
	m_Enabled = enable;
}

bool Sound::IsEnabled()
{
	return m_Enabled;
}

void Sound::PlaySound(const ActionType& type)
{
	//dont play if we are not enabled
	if (!m_Enabled) return;

	//find sound
	auto it = m_Sounds.find(type);
	if (it != m_Sounds.end()) 
	{
		//play !!
		PlaySoundA(it->second.c_str(), 0, SND_FILENAME | SND_ASYNC);
	}
}
