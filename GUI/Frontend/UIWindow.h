#pragma once

#include "UIWidget.h"
#include "../../Utils/Color.h"

class UIWindow : public UIWidget
{
private:
	bool m_Draggable;
	bool m_Drag;
	Color m_Color;

public:
	UIWindow(UIWidget* parent, UIAnchor anchor, Rect rect, Color color, bool draggable = false);
	virtual bool HandleTouchEvent(UITouchEvent* evt) override;
	virtual void Draw() override;
};