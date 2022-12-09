#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	//draw mode actions
	//shapes

	ACTION_DRAW_SHAPE_BEGIN, //mark draw mode shape beginnning

	ACTION_DRAW_SHAPE_RECTANGLE,
	ACTION_DRAW_SHAPE_SQUARE,
	ACTION_DRAW_SHAPE_TRIANGLE,
	ACTION_DRAW_SHAPE_HEXAGON,
	ACTION_DRAW_SHAPE_CIRCLE,

	ACTION_DRAW_SHAPE_END, //mark draw mode end

	//////////////////////////////////////////////////////////////////

	ACTION_DRAW_COL_BEGIN, //mark draw mode color beginnning

	ACTION_DRAW_COL_BLACK,
	ACTION_DRAW_COL_YELLOW,
	ACTION_DRAW_COL_ORANGE,
	ACTION_DRAW_COL_RED,
	ACTION_DRAW_COL_GREEN,
	ACTION_DRAW_COL_BLUE,

	ACTION_DRAW_COL_END,

	//////////////////////////////////////////////////////////////////

	ACTION_DRAW_COLMODE_BEGIN, //mark draw mode color mode beginnning

	ACTION_DRAW_COLMODE_FILL,
	ACTION_DRAW_COLMODE_DRAW,

	ACTION_DRAW_COLMODE_END,

	//////////////////////////////////////////////////////////////////

	ACTION_DRAW_OTHER_BEGIN, //mark draw mode other beginnning

	ACTION_DRAW_OTHER_SELECT,
	ACTION_DRAW_OTHER_MOVE,
	ACTION_DRAW_OTHER_DELETE_FIG,
	ACTION_DRAW_OTHER_CLEAR_ALL,
	ACTION_DRAW_OTHER_SAVE_GRAPH,
	ACTION_DRAW_OTHER_OPEN_GRAPH,
	ACTION_DRAW_OTHER_REC_START,
	ACTION_DRAW_OTHER_REC_STOP,
	ACTION_DRAW_OTHER_REC_PAUSE,
	ACTION_DRAW_OTHER_UNDO,
	ACTION_DRAW_OTHER_REDO,
	ACTION_DRAW_OTHER_PLAY,
	ACTION_DRAW_OTHER_EXIT,

	ACTION_DRAW_OTHER_END,

	//////////////////////////////////////////////////////////////////

	ACTION_PLAY_PICKHIDE_BEGIN, //mark play mode pick hide beginnning

	ACTION_PLAY_PICKHIDE_FIGTYPE,
	ACTION_PLAY_PICKHIDE_FIGCOL,
	ACTION_PLAY_PICKHIDE_FIGTYPE_COL,

	ACTION_PLAY_PICKHIDE_END,

	//////////////////////////////////////////////////////////////////

	//switch to draw mode
	ACTION_PLAY_OTHER_BEGIN,

	ACTION_PLAY_OTHER_DRAW,

	ACTION_PLAY_OTHER_END,

	//////////////////////////////////////////////////////////////////
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
enum DWShape
{
	DWSHAPE_RECTANGLE,
	DWSHAPE_SQUARE,
	DWSHAPE_TRIANGLE,
	DWSHAPE_HEXAGON,
	DWSHAPE_CIRCLE,

	DWSHAPE_COUNT
};

//Draw mode colors
enum DWColors
{
	DWCOLOR_BLACK,
	DWCOLOR_YELLOW,
	DWCOLOR_ORANGE,
	DWCOLOR_RED,
	DWCOLOR_GREEN,
	DWCOLOR_BLUE,

	DWCOLOR_COUNT
};

enum DWColorModes
{
	DWCOLORMODE_FILL,
	DWCOLORMODE_DRAW,

	DWCOLORMODE_COUNT
};

enum DWOtherActions
{
	DWOTHER_SELECT,
	DWOTHER_MOVE,
	DWOTHER_DELETE_FIG,
	DWOTHER_CLEAR_ALL,
	DWOTHER_SAVE_GRAPH,
	DWOTHER_OPEN_GRAPH,
	DWOTHER_REC_START,
	DWOTHER_REC_STOP,
	DWOTHER_REC_PAUSE,
	DWOTHER_UNDO,
	DWOTHER_REDO,
	DWOTHER_PLAY,
	DWOTHER_EXIT,

	DWOTHER_COUNT
};

enum PMPickHide
{
	PMPICKHIDE_FIG_TYPE,
	PMPICKHIDE_FIG_COL,
	PMPICKHIDE_FIG_TYPE_COL,

	PMPICKHIDE_COUNT
};

enum PMOtherAction
{
	PMOTHER_DRAW,

	PMOTHER_COUNT
};

#endif