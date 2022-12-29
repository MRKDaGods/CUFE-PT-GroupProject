#include "UIDisplay.h"

UIDisplay* UIDisplay::RenderingDisplay = 0;

UIDisplay::UIDisplay(Vector2 size) : UIWidget(0, UIAnchor::None, Rect(0.0f, 0.0f, size.x, size.y), UIWidgetType::Display)
{
	m_DownWidget = 0;
	m_FocusWidget = 0;
	m_Down = false;

	m_DisplayInfo = UIDisplayInfo {
		size.x,
		size.y,
		size.y / size.x
	};

	m_MidPoint = Vector2(size.x / 2.f, size.y / 2.f);
}

bool UIDisplay::HandleTouchEvent(UITouchEvent* evt)
{
	if (!m_Down)
	{
		m_DownWidget = FindWidget(evt->MousePosition);
	}

	if (m_DownWidget == this || !m_DownWidget)
	{
		if (m_FocusWidget)
		{
			m_FocusWidget->UpdateFocusState(false);
			m_FocusWidget = 0;
		}

		m_DownWidget = 0;
	}

	if (m_DownWidget)
	{
		if (evt->Type == UITouchEventType::Down)
		{
			m_Down = true;

			if (m_FocusWidget && m_FocusWidget != m_DownWidget)
				m_FocusWidget->UpdateFocusState(false);

			m_FocusWidget = m_DownWidget;
			m_FocusWidget->UpdateFocusState(true);
		}
		else if (evt->Type == UITouchEventType::Up)
		{
			m_Down = false;
		}

		if (m_DownWidget)
			m_DownWidget->HandleTouchEvent(evt);
	}

	if (evt->Type == UITouchEventType::Up)
	{
		UITouchEvent::Clean();
	}

	return true;
}

void UIDisplay::Draw()
{
	RenderingDisplay = this;

	//ammar: commented this to prevent flicker
	//ClearArea();

	//call base draw
	UIWidget::Draw();
}

UIDisplayInfo* UIDisplay::DisplayInfo()
{
	return &m_DisplayInfo;
}

Vector2* UIDisplay::MidScreen()
{
	return &m_MidPoint;
}
