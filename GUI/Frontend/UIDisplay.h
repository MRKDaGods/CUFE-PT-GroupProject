#pragma once

#include "UIWidget.h"

struct UIDisplayInfo
{
	float Width;
	float Height;
	float Dpr;
};

class UIDisplay : public UIWidget
{
private:
	UIWidget* m_FocusWidget;
	bool m_Down;
	UIWidget* m_DownWidget;
	UIDisplayInfo m_DisplayInfo;
	Vector2 m_MidPoint;

public:
	static UIDisplay* RenderingDisplay;

	UIDisplay(Vector2 size);
	virtual bool HandleTouchEvent(UITouchEvent* evt) override;
	virtual void Draw() override;
	UIDisplayInfo* DisplayInfo();
	Vector2* MidScreen();
};