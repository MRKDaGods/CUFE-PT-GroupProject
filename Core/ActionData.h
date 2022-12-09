#pragma once

#include <string>

#include "../DEFS.h"
#include "../GUI/Input.h"
#include "../GUI/Output.h"

//forward decleration
class Application;

//Holds information about a user action
struct ActionData
{
	//The action type
	ActionType type;

	//Message to be printed when the action occurs
	std::string status_bar_msg;

	//Callback called when the action occurs
	void(*callback)(Application*, Input*, Output*);
};

//Draw mode actions
//ActionData objects are to be instantiated once in ActionData.cpp, therefore mark as extern

//Draw rectangle
extern ActionData* action_draw_shape_rectangle;

//Draw square
extern ActionData* action_draw_shape_square;

//Draw triangle
extern ActionData* action_draw_shape_triangle;

//Draw hexagon
extern ActionData* action_draw_shape_hexagon;

//Draw circle
extern ActionData* action_draw_shape_circle;

//Color black
extern ActionData* action_draw_col_black;

//Color yellow
extern ActionData* action_draw_col_yellow;

//Color orange
extern ActionData* action_draw_col_orange;

//Color red
extern ActionData* action_draw_col_red;

//Color green
extern ActionData* action_draw_col_green;

//Color blue
extern ActionData* action_draw_col_blue;

//Colormode fill
extern ActionData* action_draw_colmode_fill;

//Colormode fill
extern ActionData* action_draw_colmode_draw;

//Other select
extern ActionData* action_draw_other_select;

//Other move
extern ActionData* action_draw_other_move;

//Other delete fig
extern ActionData* action_draw_other_delete_fig;

//Other clear all
extern ActionData* action_draw_other_clear_all;

//Other save graph
extern ActionData* action_draw_other_save_graph;

//Other open graph
extern ActionData* action_draw_other_open_graph;

//Other rec start
extern ActionData* action_draw_other_rec_start;

//Other rec stop
extern ActionData* action_draw_other_rec_stop;

//Other rec pause
extern ActionData* action_draw_other_rec_pause;

//Other undo
extern ActionData* action_draw_other_undo;

//Other redo
extern ActionData* action_draw_other_redo;

//Other playmode
extern ActionData* action_draw_other_play;

//Other exit
extern ActionData* action_draw_other_exit;

//////////////////////////////////////////////
//Play mode actions
//////////////////////////////////////////////

//PickHide figtype
extern ActionData* action_play_pickhide_figtype;

//PickHide Figcol
extern ActionData* action_play_pickhide_figcol;

//Pickhide fig type col
extern ActionData* action_play_pickhide_figtype_col;

//Other draw
extern ActionData* action_play_other_draw;