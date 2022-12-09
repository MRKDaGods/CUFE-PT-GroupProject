#pragma once

#include "UIDisplay.h"
#include "UIWindow.h"
#include "UIShapeList.h"
#include "UILabel.h"

class UIFrontend
{
private:
	UIDisplay* m_Display;
	UIWindow* m_Toolbar;
	UIWindow* m_StatusBar;
	UILabel* m_StatusBarLabel;
	UIShapeList* m_ShapeList;

public:
	UIFrontend();
	~UIFrontend();

	//Requests the main display to render
	void Render();

	//Sets the status bar text
	void SetStatusBarText(string txt);

	void HandleTouchEvent(UITouchEvent* evt);
};