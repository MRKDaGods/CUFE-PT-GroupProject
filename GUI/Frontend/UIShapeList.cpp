#include "UIShapeList.h"
#include "UIImageButton.h"
#include "UILineRenderer.h"
#include "../UI_Info.h"
#include "../../Core/Application.h"

#include <sstream>

UIShapeList::UIShapeList(UIWidget* parent, UIAnchor anchor, Rect rect, std::string shapeTextures[((int)Shape::COUNT) - 1]) 
	: UIWidget(parent, anchor, rect, UIWidgetType::ShapeList)
{
	//initialize selected shape to none
	m_SelectedShape = SHAPE_NONE;

	//create shape buttons
	for (Shape shape = SHAPE_RECTANGLE; shape < Shape::COUNT; shape = (Shape)((int)shape + 1))
	{
		int i = (int)shape - 1;
		int x = i * (UI.MenuItemWidth + UI.IconSeperatorWidth) + UI.IconPadding.left;
		UIImageButton* button = new UIImageButton(this,
			UIAnchor::None,
			Rect(x,
				UI.IconPadding.top,
				UI.MenuItemWidth - UI.IconPadding.right - UI.IconPadding.left,
				UI.ToolBarHeight - UI.IconPadding.bottom - UI.IconPadding.top
			), shapeTextures[i]);

		button->SetCallback([i]()
			{
				GetApplication()->DebugLog([i](DEBUG_LOG_PARAM)
					{
						stream << "BUTTON CLICKED IDX=" << i << endl;
				});
		});

		new UILineRenderer(this,
			UIAnchor::None,
			Rect(x + UI.MenuItemWidth, 0, 0, UI.ToolBarHeight),
			UI.IconSeperatorWidth,
			Color(0, 0, 0, 255) //black
		);
	}
}

void UIShapeList::Draw()
{
	ClearArea();

	//render children
	UIWidget::Draw();
}
