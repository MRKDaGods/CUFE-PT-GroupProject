#pragma once

#include "UIDisplay.h"
#include "UIWindow.h"
#include "UIButtonList.h"
#include "UILabel.h"

class Application;

class UIFrontend
{
private:
	Application* m_Application;
	UIDisplay* m_Display;

	//Core components
	UIWindow* m_Toolbar;
	UIWindow* m_StatusBar;
	UIWindow* m_DrawingArea;
	UILabel* m_StatusBarLabel;

	//Draw mode components
	UIButtonList* m_ShapeList;
	UIButtonList* m_ColorPalette;
	UIButtonList* m_ColorPrefList; // Fill/Draw
	UIButtonList* m_OtherActionsList;
	UILabel* m_RecordingLabel;

	//The widgets on the left for draw mode (sound, resize, move drag)
	UIWindow* m_DWLeftWidgetsContainer;

	//Play mode components
	UIButtonList* m_PickHideList;
	UIButtonList* m_PlayOtherList;

	void CreateToolBar();
	void CreateStatusBar();
	void CreateOtherElements();

	void BuildDrawModeToolBar();
	void BuildPlayModeToolBar();

	void SetDrawModeState(bool enable);
	void SetPlayModeState(bool enable);

	//Sound button callback
	void OnSoundButtonStateChanged();

	//Drag button callback
	void OnDragButtonClick();

	//Resize button callback
	void OnResizeButtonClick();

public:
	UIFrontend(Application* app);
	~UIFrontend();

	//Requests the main display to render
	void Render();

	//Sets the status bar text
	void SetStatusBarText(string txt) const;

	void HandleTouchEvent(UITouchEvent* evt);

	//Sets the current mode, false = DrawMode, true = PlayMode
	void SetCurrentMode(bool isPlayMode, bool notify = true);

	//Resets the UI state to its initial
	void Reset();

	//Sets the selected color in the button list
	void SetSelectedColor(DWColors color);

	//Sets the selected color mode in the button list
	void SetSelectedColorMode(DWColorModes mode);

	//Sets the UI recording state
	void SetRecording(bool recording, bool invokeDirty = false, std::string text = "REC");
};