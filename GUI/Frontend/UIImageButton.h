#pragma once

#include <string>
#include <functional>

#include "UIWidget.h"

class UIImageButton : public UIWidget
{
private:
	std::string m_Texture;
	bool m_Down;
	std::function<void()> m_Callback;

public:
	UIImageButton(UIWidget* parent, UIAnchor anchor, Rect rect, std::string texture);
	virtual void Draw() override;
	virtual bool HandleTouchEvent(UITouchEvent* evt) override;
	void SetCallback(std::function<void()> cb);
};