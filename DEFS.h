#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	//draw mode actions

	ACTION_DRAW_BEGIN, //mark draw mode beginnning

	ACTION_DRAW_RECTANGLE, //draw 
	ACTION_DRAW_SQUARE,
	ACTION_DRAW_TRIANGLE,
	ACTION_DRAW_HEXAGON,
	ACTION_DRAW_CIRCLE,

	ACTION_DRAW_SELECT, //select

	ACTION_DRAW_COL_BLACK,
	ACTION_DRAW_COL_YELLOW,
	ACTION_DRAW_COL_ORANGE,
	ACTION_DRAW_COL_RED,
	ACTION_DRAW_COL_GREEN,
	ACTION_DRAW_COL_BLUE,

	ACTION_DRAW_END, //mark draw mode end

	EXIT,			//Exit
	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,		//Switch interface to Play mode
	EMPTY,			//A click on empty place in the toolbar
	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar


	Draw_square,    //Draw square
	Draw_triangle,
	SelectFigure,
	Draw_heaxgon,
	Draw_circle,
	SelectColor,
	DeleteFigure,
	MoveFigure,
	Undo,
	Redo,
	ClearAll,
	StartRecording,
	StopRecording,
	PLayRecording,
	SaveGraph,
	loadGraph
};

struct Point	//To be used for figures points
{
	int x, y;
};

//Graphical info of each figure
struct GfxInfo
{
	//Draw color of the figure
	color draw_col;

	//Fill color of the figure
	color fill_col;

	//Figure Filled or not
	bool is_filled;

	//Width of figure borders
	int border_width;

	//Radius for shapes that are described by a center only (square/hexagon)
	int fixed_radius;
};

//Shapes
enum Shape
{
	SHAPE_NONE,
	SHAPE_RECTANGLE,
	SHAPE_SQUARE,
	SHAPE_TRIANGLE,
	SHAPE_HEXAGON,
	SHAPE_CIRCLE,

	COUNT
};

#endif