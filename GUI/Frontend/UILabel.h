#pragma once

#include <string>

#include "UIWidget.h"

class UILabel : UIWidget
{
private:
	int m_FontSize;
	std::string m_Text;

public:
	UILabel(UIWidget* parent, UIAnchor anchor, Rect rect, int fontSz, std::string txt);
	virtual void Draw() override;
	void SetText(std::string txt);
};

