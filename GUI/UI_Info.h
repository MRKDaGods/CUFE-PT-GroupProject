#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu
{
	DRAW_ITM_RECT,		//rectangle
	DRAW_ITM_SQUARE, //square
	DRAW_ITM_TRIANGLE, //triangle
	DRAW_ITM_HEXAGON, //hexagon
	DRAW_ITM_CIRCLE, //circle

	DRAW_ITM_SELECT, //select

	DRAW_ITM_COL_BLACK, //black
	DRAW_ITM_COL_YELLOW, //yellow
	DRAW_ITM_COL_ORANGE, //orange
	DRAW_ITM_COL_RED, //red
	DRAW_ITM_COL_GREEN, //green
	DRAW_ITM_COL_BLUE, //blue

	DRAW_ITM_COUNT,

	ITM_EXIT,
	ITM_COLOR,
	ITM_Delete,
	ITM_Undo,
	ITM_Redo,
	ITM_Clear,
	ITM_StarR,
	ITM_StopR,
	ITM_PlayR,
	ITM_SaveG,
	ITM_load,

	ITM_SWITCHP,
	
};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{

	//Note: Items are **(ordered)** here as they appear in menu
	//If you want to change the menu items order, change the order here
	
	//TODO: Add more items names here
	PICKNHIDE,
	ITM_SWITCHD,
	PLAY_ITM_COUNT,//no. of menu items ==> This should be the last line in this enum
	

};





__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;
	
	int	width, height,	    //Window width and height
		wx , wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu
	

	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes

	//Toolbar icon padding
	struct
	{
		int top;
		int bottom;
		int left;
		int right;
	} IconPadding;

	//Toolbar icon seperator width
	int IconSeperatorWidth;
	
}UI;	//create a global object UI

#endif