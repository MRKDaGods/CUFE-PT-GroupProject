#pragma once

#include "UIWidget.h"
#include "../../DEFS.h"

class UIShapeList : public UIWidget
{
private:
	Shape m_SelectedShape;

public:
	UIShapeList(UIWidget* parent, UIAnchor anchor, Rect rect, std::string shapeTextures[((int)Shape::COUNT) - 1]); //-1 to ignore the "None" shape
	virtual void Draw() override;
};

