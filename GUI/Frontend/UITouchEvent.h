#pragma once

#include "../../Utils/Vector2.h"

enum class UITouchEventType 
{
	None,
	Up,
	Down,
	Drag
};

struct UITouchEvent
{
private:
	static Vector2 ms_LastMousePosition;

public:
	UITouchEventType Type;
	Vector2 MousePosition;

	UITouchEvent(float x, float y, UITouchEventType type);

	Vector2 Delta();

	void Consume();

	static void Clean();
};