#include "UIImageButton.h"
#include "UISprite.h"
#include "../../Core/Application.h"

UIImageButton::UIImageButton(UIWidget* parent, UIAnchor anchor, Rect rect, std::string texture) : UIWidget(parent, anchor, rect, UIWidgetType::Button)
{
	m_Texture = texture;
}

void UIImageButton::Draw()
{
	//ClearArea();

	//render sprite manually for now
	//maybe add a sprite child later?
	GetApplication()->GetOutput()->DrawImage(ScreenRect(), m_Texture);

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
