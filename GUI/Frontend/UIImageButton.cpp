#include "UIImageButton.h"
#include "UISprite.h"
#include "../../Core/Application.h"

UIImageButton::UIImageButton(UIWidget* parent, UIAnchor anchor, Rect rect, std::string texture, Color selColor) : UIWidget(parent, anchor, rect, UIWidgetType::Button)
{
	m_Texture = texture;
	m_Selected = false;
	m_SelectedColor = selColor;
}

void UIImageButton::Draw()
{
	//ClearArea();

	//render sprite manually for now
	//maybe add a sprite child later?

	Output* output = GetApplication()->GetOutput();

	output->DrawImage(ScreenRect(), m_Texture);

	if (m_Selected)
	{
		output->DrawRect(ScreenRect(), m_SelectedColor, false, 4);
	}

	UIWidget::Draw();
}

bool UIImageButton::HandleTouchEvent(UITouchEvent* evt)
{
	if (evt->Type == UITouchEventType::Down)
	{
		m_Down = true;

		if (m_Callback)
		{
			m_Callback();
		}
	}
	else if (evt->Type == UITouchEventType::Up)
	{
		m_Down = false;
	}

	return true;
}

void UIImageButton::SetCallback(std::function<void()> cb)
{
	m_Callback = cb;
}

void UIImageButton::SetSelected(bool selected, bool notify)
{
	m_Selected = selected;

	if (notify)
	{
		Invalidate();
	}
}
