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

//Other exit
extern ActionData* action_draw_other_exit;