#pragma once

#include "UIWidget.h"
#include "../../Utils/Color.h"

class UILineRenderer : UIWidget
{
private:
	int m_Width;
	Color m_Color;

public:
	UILineRenderer(UIWidget* parent, UIAnchor anchor, Rect rect, int width, Color col);
	virtual void Draw() override;
};

