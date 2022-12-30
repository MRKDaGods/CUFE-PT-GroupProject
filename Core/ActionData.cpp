#include "ActionData.h"
#include "Application.h"

//macro for draw shape message
#define MESSAGE_DRAW_SHAPE(name) "Action: Draw a " #name ", Click anywhere"
#define MESSAGE_COL(name) "Action: Selected Color " #name
#define MESSAGE_COLMODE(name) "Action: Selected ColorMode " #name
#define MESSAGE_OTHER(name) "Action: " #name

//Implement actions

//Draw mode actions

//////////////////////////////////////////////
//Shape actions
//////////////////////////////////////////////
ActionData* action_draw_shape_rectangle = new ActionData {
	ACTION_DRAW_SHAPE_RECTANGLE,
	MESSAGE_DRAW_SHAPE(RECTANGLE),

	//action callback
	[](Application* app, Input* in, Output* out) 
	{
		Point topLeft, botRight;

		//get first point
		in->GetPointClicked(topLeft.x, topLeft.y);

		//get second point
		in->GetPointClicked(botRight.x, botRight.y);

		//draw rectangle
		out->DrawRectangle(topLeft, botRight);
	}
};

ActionData* action_draw_shape_square = new ActionData{
	ACTION_DRAW_SHAPE_SQUARE,
	MESSAGE_DRAW_SHAPE(SQUARE),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		Point center;

		//get center
		in->GetPointClicked(center.x, center.y);

		//draw square
		out->DrawSquare(center);
	}
};

ActionData* action_draw_shape_triangle = new ActionData{
	ACTION_DRAW_SHAPE_TRIANGLE,
	MESSAGE_DRAW_SHAPE(TRIANGLE),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		Point v1, v2, v3;

		//get 3 vertices
		in->GetPointClicked(v1.x, v1.y);
		in->GetPointClicked(v2.x, v2.y);
		in->GetPointClicked(v3.x, v3.y);

		//draw triangle
		out->DrawTriangle(v1, v2, v3);
	}
};

ActionData* action_draw_shape_hexagon = new ActionData{
	ACTION_DRAW_SHAPE_HEXAGON,
	MESSAGE_DRAW_SHAPE(HEXAGON),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		Point center;

		//get center
		in->GetPointClicked(center.x, center.y);

		//draw hexagon
		out->DrawHexagon(center);
	}
};

ActionData* action_draw_shape_circle = new ActionData{
	ACTION_DRAW_SHAPE_CIRCLE,
	MESSAGE_DRAW_SHAPE(CIRCLE),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		Point center, radiusPoint;

		//get center
		in->GetPointClicked(center.x, center.y);

		//get radiusPoint
		in->GetPointClicked(radiusPoint.x, radiusPoint.y);

		//draw circle
		out->DrawCircle(center, radiusPoint);
	}
};

//////////////////////////////////////////////
//Color actions
//////////////////////////////////////////////

ActionData* action_draw_col_black = new ActionData{
	ACTION_DRAW_COL_BLACK,
	MESSAGE_COL(BLACK),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//app->SetDrawModeColor(DWCOLOR_BLACK);
	}
};

ActionData* action_draw_col_yellow = new ActionData{
	ACTION_DRAW_COL_YELLOW,
	MESSAGE_COL(YELLOW),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//app->SetDrawModeColor(DWCOLOR_YELLOW);
	}
};

ActionData* action_draw_col_orange = new ActionData{
	ACTION_DRAW_COL_ORANGE,
	MESSAGE_COL(ORANGE),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//app->SetDrawModeColor(DWCOLOR_ORANGE);
	}
};

ActionData* action_draw_col_red = new ActionData{
	ACTION_DRAW_COL_RED,
	MESSAGE_COL(RED),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//app->SetDrawModeColor(DWCOLOR_RED);
	}
};

ActionData* action_draw_col_green = new ActionData{
	ACTION_DRAW_COL_GREEN,
	MESSAGE_COL(GREEN),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//app->SetDrawModeColor(DWCOLOR_GREEN);
	}
};

ActionData* action_draw_col_blue = new ActionData{
	ACTION_DRAW_COL_BLUE,
	MESSAGE_COL(BLUE),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//app->SetDrawModeColor(DWCOLOR_BLUE);
	}
};

//////////////////////////////////////////////
//ColorMode actions
//////////////////////////////////////////////
ActionData* action_draw_colmode_fill = new ActionData{
	ACTION_DRAW_COLMODE_FILL,
	MESSAGE_COLMODE(FILL),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		app->SetCurrentColorMode(DWCOLORMODE_FILL);
	}
};

ActionData* action_draw_colmode_draw = new ActionData{
	ACTION_DRAW_COLMODE_DRAW,
	MESSAGE_COLMODE(DRAW),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		app->SetCurrentColorMode(DWCOLORMODE_DRAW);
	}
};


//////////////////////////////////////////////
//Other actions
//////////////////////////////////////////////
ActionData* action_draw_other_select = new ActionData{
	ACTION_DRAW_OTHER_SELECT,
	MESSAGE_OTHER(SELECT),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement select
	}
};

ActionData* action_draw_other_move = new ActionData{
	ACTION_DRAW_OTHER_MOVE,
	MESSAGE_OTHER(MOVE),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement move
	}
};

ActionData* action_draw_other_delete_fig = new ActionData{
	ACTION_DRAW_OTHER_DELETE_FIG,
	MESSAGE_OTHER(DELETE FIGURE),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement delete fig
	}
};

ActionData* action_draw_other_clear_all = new ActionData{
	ACTION_DRAW_OTHER_CLEAR_ALL,
	MESSAGE_OTHER(CLEAR ALL),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement clear all
	}
};

ActionData* action_draw_other_save_graph = new ActionData{
	ACTION_DRAW_OTHER_SAVE_GRAPH,
	MESSAGE_OTHER(SAVE GRAPH),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement save graph
	}
};

ActionData* action_draw_other_open_graph = new ActionData{
	ACTION_DRAW_OTHER_OPEN_GRAPH,
	MESSAGE_OTHER(OPEN GRAPH),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement open graph
	}
};

ActionData* action_draw_other_rec_start = new ActionData{
	ACTION_DRAW_OTHER_REC_START,
	MESSAGE_OTHER(RECORDING STARTED),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement rec start
	}
};

ActionData* action_draw_other_rec_stop = new ActionData{
	ACTION_DRAW_OTHER_REC_STOP,
	MESSAGE_OTHER(RECORDING STOP),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement rec stop
	}
};

ActionData* action_draw_other_rec_pause = new ActionData{
	ACTION_DRAW_OTHER_REC_PAUSE,
	MESSAGE_OTHER(RECORDING PAUSE),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement rec pause
	}
};

ActionData* action_draw_other_undo = new ActionData{
	ACTION_DRAW_OTHER_UNDO,
	MESSAGE_OTHER(UNDO),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement undo
	}
};

ActionData* action_draw_other_redo = new ActionData{
	ACTION_DRAW_OTHER_REDO,
	MESSAGE_OTHER(REDO),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement redo
	}
};

ActionData* action_draw_other_play = new ActionData{
	ACTION_DRAW_OTHER_PLAY,
	MESSAGE_OTHER(PLAY MODE),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//switch to play mode
		app->SetCurrentMode(true);
	}
};

ActionData* action_draw_other_exit = new ActionData{
	ACTION_DRAW_OTHER_EXIT,
	MESSAGE_OTHER(EXIT),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		app->Exit();
	}
};

//////////////////////////////////////////////
//Play mode actions
//////////////////////////////////////////////

ActionData* action_play_pickhide_figtype = new ActionData{
	ACTION_PLAY_PICKHIDE_FIGTYPE,
	MESSAGE_OTHER(PICK HIDE FIGURE TYPE),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement figtype
	}
};

ActionData* action_play_pickhide_figcol = new ActionData{
	ACTION_PLAY_PICKHIDE_FIGCOL,
	MESSAGE_OTHER(PICK HIDE FIGURE COLOR),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement figcol
	}
};

ActionData* action_play_pickhide_figtype_col = new ActionData{
	ACTION_PLAY_PICKHIDE_FIGTYPE_COL,
	MESSAGE_OTHER(PICK HIDE FIGURE TYPE AND COLOR),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//TODO: implement figtype col
	}
};

ActionData* action_play_other_draw = new ActionData{
	ACTION_PLAY_OTHER_DRAW,
	MESSAGE_OTHER(DRAW MODE),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		//switch to draw mode
		app->SetCurrentMode(false);
	}
};