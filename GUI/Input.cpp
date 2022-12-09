#include "Input.h"
#include "Output.h"


Input::Input(window* pW) 
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetString(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

Point Input::GetMousePos()
{
	Point p;
	pWind->GetMouseCoord(p.x, p.y);

	return p;
}

bool Input::GetMouseDown()
{
	Point p;
	return pWind->GetMouseClick(p.x, p.y) != NO_CLICK;
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	return ACTION_DRAW_COLMODE_BEGIN;

	/*int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = x / (UI.MenuItemWidth + UI.IconSeperatorWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			/*switch (ClickedItemOrder)
			{
			case DRAW_ITM_RECT: return ACTION_DRAW_SHAPE_RECTANGLE;
			case DRAW_ITM_SQUARE: return ACTION_DRAW_SHAPE_SQUARE;
			case DRAW_ITM_TRIANGLE: return ACTION_DRAW_SHAPE_TRIANGLE;
			case DRAW_ITM_HEXAGON: return ACTION_DRAW_SHAPE_HEXAGON;
			case DRAW_ITM_CIRCLE: return ACTION_DRAW_SHAPE_CIRCLE;
			case DRAW_ITM_SELECT: return ACTION_DRAW_SELECT;
			case DRAW_ITM_COL_BLACK: return ACTION_DRAW_COL_BLACK;
			case DRAW_ITM_COL_YELLOW: return ACTION_DRAW_COL_YELLOW;
			case DRAW_ITM_COL_ORANGE: return ACTION_DRAW_COL_ORANGE;
			case DRAW_ITM_COL_RED: return ACTION_DRAW_COL_RED;
			case DRAW_ITM_COL_GREEN: return ACTION_DRAW_COL_GREEN;
			case DRAW_ITM_COL_BLUE: return ACTION_DRAW_COL_BLUE;



			case ITM_SWITCHP: return TO_PLAY;
			//case ITM_EXIT: return EXIT;	
			
			default: return EMPTY;	//A click on empty place in desgin toolbar
			}
		}

		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;	
		}
		
		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
			case ITM_SWITCHD: return TO_DRAW;
			//case ITM_EXIT: return EXIT;
			}

		}

		///TODO:
		//perform checks similar to Draw mode checks above
		//and return the correspoding action
		return TO_PLAY;	//just for now. This should be updated
	}	*/

}
/////////////////////////////////
	
Input::~Input()
{
}
