#pragma once

#include "UIImageButton.h"

class UIToggleButton : public UIImageButton
{
private:
	//The enabled texture
	std::string m_OnTexture;

	//Callback provided by user as we are overriding our own
	std::function<void()> m_UserCallback;

	//Mouse down callback
	void OnDown();

public:
	UIToggleButton(UIWidget* parent, UIAnchor anchor, Rect rect, std::string offTex, std::string onTex);
	virtual void Draw() override;
	virtual void SetCallback(std::function<void()> cb);
};

