#pragma once

#include "UIDisplay.h"
#include "UIWindow.h"
#include "UIButtonList.h"
#include "UILabel.h"

class UIFrontend
{
private:
	UIDisplay* m_Display;

	//Core components
	UIWindow* m_Toolbar;
	UIWindow* m_StatusBar;
	UILabel* m_StatusBarLabel;

	//Draw mode components
	UIButtonList* m_ShapeList;
	UIButtonList* m_ColorPalette;
	UIButtonList* m_ColorPrefList; // Fill/Draw
	UIButtonList* m_OtherActionsList;

	void CreateToolBar();
	void CreateStatusBar();

public:
	UIFrontend();
	~UIFrontend();

	//Requests the main display to render
	void Render();

	//Sets the status bar text
	void SetStatusBarText(string txt);

	void HandleTouchEvent(UITouchEvent* evt);
};