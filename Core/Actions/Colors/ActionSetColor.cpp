#include "ActionSetColor.h"

#include "../../Application.h"

ActionSetColor::ActionSetColor(Application* app, DWColors color) : Action(app)
{
	m_Color = color;
	m_OldColor = m_Application->GetCurrentColor();

	m_ColorMode = m_Application->GetCurrentColorMode();

	m_OldFillState = m_Application->GetGfxInfo()->is_filled;
}

void ActionSetColor::SetColor(DWColors col, bool restoreFillState)
{
	m_Application->SetCurrentColorMode(m_ColorMode);

	//set color in app
	m_Application->SetCurrentColor(col);

	std::string colStr = ""; //color string
	std::string modeStr = ""; //color mode string (fill / draw)

	color c;
	switch (col)
	{
	case DWCOLOR_BLACK:
		c = BLACK;
		colStr = "BLACK";
		break;

	case DWCOLOR_YELLOW:
		c = YELLOW;
		colStr = "YELLOW";
		break;

	case DWCOLOR_ORANGE:
		c = ORANGE;
		colStr = "ORANGE";
		break;

	case DWCOLOR_RED:
		c = RED;
		colStr = "RED";
		break;

	case DWCOLOR_GREEN:
		c = GREEN;
		colStr = "GREEN";
		break;

	case DWCOLOR_BLUE:
		c = BLUE;
		colStr = "BLUE";
		break;

	case DWCOLOR_COUNT:
		break;
	}

	GfxInfo* globalGfxInfo = m_Application->GetGfxInfo();

	//check if we have a selected figure to modify
	CFigure* selectedFig = m_Application->GetSelectedFigure();

	switch (m_Application->GetCurrentColorMode())
	{
	case DWCOLORMODE_FILL:
		globalGfxInfo->fill_col = c;
		if (selectedFig != 0)
		{
			if (!restoreFillState)
			{
				m_OldFillState = selectedFig->GetGfxInfo()->is_filled;
			}

			selectedFig->ChangeFillColor(globalGfxInfo->fill_col);
		}

		modeStr = "FILL";
		break;

	case DWCOLORMODE_DRAW:
		globalGfxInfo->draw_col = c;
		if (selectedFig != 0)
		{
			selectedFig->ChangeDrawColor(globalGfxInfo->draw_col);
		}

		modeStr = "DRAW";
		break;

	case DWCOLORMODE_COUNT:
		break;
	}

	//output the selected color and mode
	m_Frontend->SetStatusBarText("COLOR: Set " + modeStr + " color to " + colStr);

	if (selectedFig != 0)
	{
		if (restoreFillState)
		{
			selectedFig->GetGfxInfo()->is_filled = m_OldFillState;
		}

		//notify application to update
		m_Application->Render(true);
	}
}

void ActionSetColor::ReadActionParameters()
{
}

void ActionSetColor::Execute()
{
	SetColor(m_Color, false);
}

void ActionSetColor::Undo()
{
	//update frontend as well
	m_Frontend->SetSelectedColor(m_OldColor);

	//update color
	SetColor(m_OldColor, true);
}

ActionType ActionSetColor::GetActionType()
{
	switch (m_Color)
	{
	case DWCOLOR_BLACK:
		return ACTION_DRAW_COL_BLACK;

	case DWCOLOR_YELLOW:
		return ACTION_DRAW_COL_YELLOW;

	case DWCOLOR_ORANGE:
		return ACTION_DRAW_COL_ORANGE;

	case DWCOLOR_RED:
		return ACTION_DRAW_COL_RED;

	case DWCOLOR_GREEN:
		return ACTION_DRAW_COL_GREEN;

	case DWCOLOR_BLUE:
		return ACTION_DRAW_COL_BLUE;

	case DWCOLOR_COUNT:
		break;
	}

	return ACTION_DRAW_COL_BEGIN;
}
