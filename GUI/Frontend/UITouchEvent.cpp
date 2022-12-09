#include "UITouchEvent.h"

Vector2 UITouchEvent::ms_LastMousePosition = Vector2::Zero;

UITouchEvent::UITouchEvent(float x, float y, UITouchEventType type)
{
	MousePosition = Vector2(x, y);
	Type = type;

	if (ms_LastMousePosition == Vector2::Zero)
	{
		ms_LastMousePosition = MousePosition;
	}
}

Vector2 UITouchEvent::Delta()
{
	return MousePosition - ms_LastMousePosition;
}

void UITouchEvent::Consume()
{
	ms_LastMousePosition = MousePosition;
}

void UITouchEvent::Clean()
{
	ms_LastMousePosition = Vector2::Zero;
}