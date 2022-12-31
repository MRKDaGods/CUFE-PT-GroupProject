#pragma once

#include "../Action.h"
#include "../../../DEFS.h"

#include <vector>
#include <string>

class CFigure;

class ActionPickAndHide : public Action
{
private:
	PMPickHide m_Mode;
	
	//Array of distinct colors in the graph
	std::vector<color> m_Colors;

	//Array of distinct shapes in the graph;
	std::vector<DWShape> m_Shapes;

	//The target color
	color m_TargetColor;

	//The target shape
	DWShape m_TargetShape;

	//Maximum grade to be achieved (count of objective)
	int m_MaxGrade;

	//Number of incorrect selections
	int m_Incorrect;

	//Number of correct selections
	int m_Correct;

	//The game title, ex: Pick all blue triangles, etc
	std::string m_GameTitle;

	//Initialize the game data and picks the objective
	void InitGameData();

	//Returns true if the figure matches the game rules
	bool FigureMeetsRequirements(CFigure* fig);

	//Converts a shape to a string
	std::string ShapeToString(DWShape shape);

	//Converts a color to a string
	std::string ColorToString(color col);

public:
	ActionPickAndHide(Application* app, PMPickHide pickHideMode);

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual ActionType GetActionType() override;
};