#include "UIWidget.h"
#include "../../Core/Application.h"
#include "UIDisplay.h"

UIWidget::UIWidget(UIWidget* parent, UIAnchor anchor, Rect rect, UIWidgetType type)
{
	m_Parent = parent;
	m_Anchor = anchor;
	m_Focused = false;
	m_Type = type;
	m_Visible = true;
	m_DontHandleTouch = false;

	if (parent)
	{
		parent->AddChild(this);
	}

	m_Rect = rect;
	m_Position = rect.Position();
	m_Size = rect.Size();

	if (anchor != UIAnchor::None)
	{
		RecalculateAnchors();
	}

	m_Focused = true;
}

UIWidget::~UIWidget()
{
	for (UIWidget*& widget : m_Children)
	{
		if (widget)
		{
			delete widget;
			widget = 0;
		}
	}
}

UIWidget* UIWidget::FindWidget(Vector2 pos)
{
	//iterate backwards
	for (auto rv = m_Children.rbegin(); rv != m_Children.rend(); rv++)
	{
		UIWidget* widget = *rv;
		if (!widget->Visible() || widget->DontHandleTouch())
			continue;

		if (widget->ScreenRect().Contains(pos))
			return widget;
	}

	return 0;
}

void UIWidget::UpdateFocusState(bool focused, bool withChildren)
{
	m_Focused = true;

	if (m_Parent && m_Parent->Type() != UIWidgetType::Display)
	{
		m_Parent->UpdateFocusState(true, false);
	}

	if (!withChildren) return;

	for (UIWidget*& widget : m_Children)
	{
		widget->UpdateFocusState(focused);
	}
}

bool UIWidget::HandleTouchEvent(UITouchEvent* evt)
{
	UIWidget* widget = FindWidget(evt->MousePosition);
	if (widget)
	{
		return widget->HandleTouchEvent(evt);
	}

	return false;
}

void UIWidget::Draw()
{
	if (!m_Visible)
		return;

	//render all widgets in the subtree
	for (UIWidget*& widget : m_Children)
	{
		if (widget->Visible())
		{
			widget->Draw();
		}
	}
}

void UIWidget::SetVisible(bool visible, bool invokeDirty)
{
	m_Visible = visible;

	for (UIWidget*& widget : m_Children)
	{
		widget->SetVisible(visible, false);
	}

	if (invokeDirty)
	{
		Invalidate();
	}
}

Vector2 UIWidget::Position()
{
	if (m_Parent)
	{
		return m_Parent->Position() + m_Position;
	}

	return m_Position;
}

bool UIWidget::Visible()
{
	return m_Visible;
}

bool UIWidget::DontHandleTouch()
{
	return m_DontHandleTouch;
}

void UIWidget::SetDontHandleTouch(bool val)
{
	m_DontHandleTouch = val;
}

Rect UIWidget::ScreenRect()
{
	Vector2 pos = Position();
	return Rect(pos.x, pos.y, m_Size.x, m_Size.y);
}

void UIWidget::AddChild(UIWidget* child)
{
	m_Children.push_back(child);
}

UIWidgetType UIWidget::Type()
{
	return m_Type;
}

void UIWidget::RecalculateAnchors()
{
	float x = 0.f;
	float y = 0.f;

	if (m_Anchor == UIAnchor::None)
	{
		x = m_Position.x;
		y = m_Position.y;
	}
	else
	{
		float sw = m_Parent->m_Size.x;
		float sh = m_Parent->m_Size.y;

		if (m_Anchor & UIAnchor::Left)
		{
			x = m_Position.x;
		}
		else if (m_Anchor & UIAnchor::Center)
		{
			x = sw / 2.f + m_Position.x;
		}
		else if (m_Anchor & UIAnchor::Right)
		{
			x = sw - m_Position.x;
		}

		if (m_Anchor & UIAnchor::Top)
		{
			y = m_Position.y;
		}
		else if (m_Anchor & UIAnchor::Middle)
		{
			y = sh / 2.f + m_Position.y;
		}
		else if (m_Anchor & UIAnchor::Bottom)
		{
			y = sh - m_Position.y;
		}
	}

	m_Position = Vector2(x, y);
	NotifyConstraintChanged();
}

void UIWidget::ClearArea()
{
	GetApplication()->GetOutput()->ClearArea(ScreenRect());
}

void UIWidget::NotifyConstraintChanged()
{
	m_Rect = Rect(m_Position.x, m_Position.y, m_Size.x, m_Size.y);
}

void UIWidget::Invalidate()
{
	//for now, just refresh the whole screen buffer by rendering the display again
	UIDisplay::RenderingDisplay->Draw();
}

int operator&(UIAnchor right, UIAnchor left)
{
	return ((int)right) & ((int)left);
}

UIAnchor operator|(UIAnchor right, UIAnchor left)
{
	return (UIAnchor)(((int)right) | ((int)left));
}