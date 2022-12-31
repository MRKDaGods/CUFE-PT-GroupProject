#pragma once

#include "../DEFS.h"
#include "../Utils/Rect.h"

class Output;

class FigureNode
{
private:
	Point m_Pos;

	//Returns the screenspace rect
	Rect GetRect();

public:
	FigureNode();

	//Sets the position of the node
	void SetPosition(Point p);

	//Returns the node's position
	Point GetPosition();

	//Returns true if hit test is successful
	bool HitTest(Point p);

	//Renders the node
	void RenderNode(Output* output);
};