#include "ActionData.h"
#include "Application.h"

//macro for draw shape message
#define MESSAGE_DRAW_SHAPE(name) "Action: Draw a " #name ", Click anywhere"
#define MESSAGE_OTHER(name) "Action: " #name

//Implement actions

//Draw mode actions
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
//Other actions
//////////////////////////////////////////////

ActionData* action_draw_other_exit = new ActionData{
	ACTION_DRAW_OTHER_EXIT,
	MESSAGE_OTHER(EXIT),

	//action callback
	[](Application* app, Input* in, Output* out)
	{
		app->Exit();
	}
};