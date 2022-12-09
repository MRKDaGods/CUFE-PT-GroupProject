#include "UIButtonList.h"
#include "UIImageButton.h"
#include "UILineRenderer.h"
#include "../UI_Info.h"
#include "../../Core/Application.h"

#include <sstream>

void UIButtonList::UpdateSelectedButton(int idx)
{
	if (!m_Selectable) return;

	if (m_SelectedButton != -1)
	{
		m_Buttons[m_SelectedButton]->SetSelected(false, false);
	}

	m_SelectedButton = idx;
	m_Buttons[m_SelectedButton]->SetSelected(true);
}

UIButtonList::UIButtonList(UIWidget* parent, UIAnchor anchor, Rect rect, bool selectable, int count, std::string* shapeTextures, ActionType* actions, Color selectColor)
	: UIWidget(parent, anchor, rect, UIWidgetType::ShapeList)
{
	//initialize selected shape to none
	m_SelectedButton = -1;

	m_Selectable = selectable;

	//create shape buttons
	for (int i = 0; i < count; i++)
	{
		int x = i * (UI.MenuItemWidth + UI.IconSeperatorWidth) + UI.IconPadding.left;
		UIImageButton* button = new UIImageButton(this,
			UIAnchor::None,
			Rect(x,
				UI.IconPadding.top,
				UI.MenuItemWidth - UI.IconPadding.right /*- UI.IconPadding.left */,
				UI.ToolBarHeight - UI.IconPadding.bottom - UI.IconPadding.top
			), shapeTextures[i], selectColor);

		ActionType currentAction = actions[i];
		button->SetCallback(
			[this, i, currentAction]() 
			{
				GetApplication()->DebugLog([i](DEBUG_LOG_PARAM) { stream << "BUTTON CLICKED IDX=" << i << endl; });

				UpdateSelectedButton(i);

				GetApplication()->HandleAction(currentAction);
			}
		);

		//add button to vector
		m_Buttons.push_back(button);

		new UILineRenderer(this,
			UIAnchor::None,
			Rect(x + UI.MenuItemWidth, 0, 0, UI.ToolBarHeight),
			UI.IconSeperatorWidth,
			Color(0, 0, 0, 255) //black
		);
	}
}

void UIButtonList::Draw()
{
	//ClearArea();

	//render children
	UIWidget::Draw();
}
