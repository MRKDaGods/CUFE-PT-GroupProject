#include "UIToggleButton.h"
#include "../../Core/Application.h"

UIToggleButton::UIToggleButton(UIWidget* parent, UIAnchor anchor, Rect rect, std::string offTex, std::string onTex) : UIImageButton(parent, anchor, rect, offTex, Color())
{
	m_OnTexture = onTex;
	
	//assign local callback
	m_Callback = std::bind(&UIToggleButton::OnDown, this);
}

void UIToggleButton::Draw()
{
	Output* output = GetApplication()->GetOutput();

	//draw the appropriate texture
	output->DrawImage(ScreenRect(), m_Selected ? m_OnTexture : m_Texture);

	UIWidget::Draw();
}

void UIToggleButton::SetCallback(std::function<void()> cb)
{
	m_UserCallback = cb;
}

void UIToggleButton::OnDown()
{
	m_Selected = !m_Selected;

	if (m_UserCallback != 0)
	{
		m_UserCallback();
	}

	Invalidate();
}