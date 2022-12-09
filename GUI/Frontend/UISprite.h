#pragma once

#include <string>

#include "UIWidget.h"

class UISprite : public UIWidget
{
private:
	std::string m_Texture;

public:
	UISprite(UIWidget* parent, UIAnchor anchor, Rect rect, std::string texture);
	virtual void Draw() override;
};