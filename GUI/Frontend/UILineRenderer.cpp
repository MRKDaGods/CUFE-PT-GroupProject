#include "UILineRenderer.h"
#include "../../Core/Application.h"

UILineRenderer::UILineRenderer(UIWidget* parent, UIAnchor anchor, Rect rect, int width, Color col) : UIWidget(parent, anchor, rect, UIWidgetType::LineRenderer)
{
	m_Width = width;
	m_Color = col;
}

void UILineRenderer::Draw()
{
    //ClearArea();

    Rect rect = ScreenRect();
    GetApplication()->GetOutput()->DrawLine(rect.Position(), rect.Position() + rect.Size(), m_Width, m_Color);

    UIWidget::Draw();
}
