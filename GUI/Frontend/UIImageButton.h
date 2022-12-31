#pragma once

#include <string>
#include <functional>

#include "UIWidget.h"
#include "../../Utils/Color.h"

class UIImageButton : public UIWidget
{
protected:
	std::string m_Texture;
	bool m_Down;
	std::function<void()> m_Callback;
	bool m_Selected;
	Color m_SelectedColor;

public:
	UIImageButton(UIWidget* parent, UIAnchor anchor, Rect rect, std::string texture, Color selColor);
	virtual void Draw() override;
	virtual bool HandleTouchEvent(UITouchEvent* evt) override;
	virtual void SetCallback(std::function<void()> cb);
	void SetSelected(bool selected, bool notify = true);
};