#include "UISprite.h"
#include "../../Core/Application.h"

UISprite::UISprite(UIWidget* parent, UIAnchor anchor, Rect rect, std::string texture) :
	UIWidget(parent, anchor, rect, UIWidgetType::Sprite)
{
	m_Texture = texture;
}

void UISprite::Draw()
{
	//Clear area first
	ClearArea();

	//Draw texture
	GetApplication()->GetOutput()->DrawImage(ScreenRect(), m_Texture);

	//Render children if exists
	UIWidget::Draw();
}