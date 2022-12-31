#include "UILabel.h"
#include "../../Core/Application.h"

UILabel::UILabel(UIWidget* parent, UIAnchor anchor, Rect rect, int fontSz, std::string txt) : UIWidget(parent, anchor, rect, UIWidgetType::Label)
{
	m_FontSize = fontSz;
	m_Text = txt;
}

void UILabel::Draw()
{
	//center label in rect
	Rect rect = ScreenRect();
	rect.y += m_FontSize * 0.5;

	GetApplication()->GetOutput()->DrawString(rect, m_Text, m_FontSize);

	UIWidget::Draw();
}

void UILabel::SetText(std::string txt, bool notify)
{
	//dont update if same value
	if (m_Text == txt) return;

	m_Text = txt;
	
	if (notify)
	{
		//invalidate
		Invalidate();
	}
}
