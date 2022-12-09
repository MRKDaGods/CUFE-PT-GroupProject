#pragma once

#include <functional>

#include "UIWidget.h"
#include "../../Utils/Color.h"

class UIWindow : public UIWidget
{
private:
	bool m_Draggable;
	bool m_Drag;
	Color m_Color;
	std::function<void()> m_OnDown;

public:
	UIWindow(UIWidget* parent, UIAnchor anchor, Rect rect, Color color, bool draggable = false, std::function<void()> onDown = 0);
	virtual bool HandleTouchEvent(UITouchEvent* evt) override;
	virtual void Draw() override;
};