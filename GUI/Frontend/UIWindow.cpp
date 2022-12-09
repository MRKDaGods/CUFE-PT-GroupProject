#include "UIWindow.h"
#include "UIDisplay.h"
#include "../../Core/Application.h"

//Clamps a number between min and max
template <typename T>
T clamp(T x, T min, T max)
{
    if (x < min) x = min;
    if (x > max) x = max;
    return x;
}

UIWindow::UIWindow(UIWidget* parent, UIAnchor anchor, Rect rect, Color color, bool draggable)
	: UIWidget(parent, anchor, rect, UIWidgetType::Window)
{
    m_Drag = false;
    m_Color = color;
	m_Draggable = draggable;
}

bool UIWindow::HandleTouchEvent(UITouchEvent* evt)
{
    if (UIWidget::HandleTouchEvent(evt))
        return false;

    switch (evt->Type)
    {
    case UITouchEventType::Down:
        if (m_Draggable)
        {
            m_Drag = true;
        }

        evt->Consume(); //H

        break;

    case UITouchEventType::Drag:
        if (m_Drag)
        {
            m_Position += evt->Delta();

            UIDisplayInfo* displayInfo = UIDisplay::RenderingDisplay->DisplayInfo();
            m_Position = Vector2(clamp(m_Position.x, 0.f, displayInfo->Width - m_Size.x),
                clamp(m_Position.y, 0.f, displayInfo->Height - m_Size.y));

            evt->Consume();
            NotifyConstraintChanged();
        }
        break;

    case UITouchEventType::Up:
        m_Drag = false;
        break;
    }

    return true;
}

void UIWindow::Draw()
{
    //ClearArea();

    GetApplication()->GetOutput()->DrawRect(ScreenRect(), m_Color);

    UIWidget::Draw();
}
