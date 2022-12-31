#pragma once

#include "UIWidget.h"
#include "UIImageButton.h"
#include "../../DEFS.h"

class UIButtonList : public UIWidget
{
private:
	int m_SelectedButton;
	std::vector<UIImageButton*> m_Buttons;
	bool m_Selectable;

public:
	UIButtonList(UIWidget* parent, UIAnchor anchor, Rect rect, bool selectable, int count, std::string* shapeTextures, ActionType* actions, Color selectColor);
	virtual void Draw() override;
	void UpdateSelectedButton(int idx, bool notify = true);
};

