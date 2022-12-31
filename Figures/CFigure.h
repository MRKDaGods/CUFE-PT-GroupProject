#pragma once

#include "../Common.h"
#include "../DEFS.h"
#include "../GUI/Output.h"
#include "../Core/Serializer.h"
#include "../Core/Deserializer.h"
#include "FigureNode.h"

class UIFrontend;

//Base class for all figures
class CFigure
{
protected:
	int m_ID;
	bool m_Selected;
	GfxInfo m_GfxInfo;

	//Indicates whether nodes should be drawn or not
	bool m_ShouldRenderNodes;

	//Implemented in all figures to fill nodes with node array
	virtual void GetNodes(FigureNode*** nodes, int* sz) abstract;

public:
	CFigure(int figID, GfxInfo gfxInfo);

	//Returns the unique figure ID
	int GetID();

	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	GfxInfo* GetGfxInfo();

	//Sets whether nodes should be rendered or not
	void SetNodeRenderingState(bool render);

	//Finds a node at position p
	FigureNode* GetNode(Point p);

	virtual void Draw(Output* pOut) abstract;		//Draw the figure

	void ChangeDrawColor(color Dclr);	//changes the figure's drawing color
	void ChangeFillColor(color Fclr);	//changes the figure's filling color

	virtual bool HitTest(Point hit) abstract;
	virtual void PrintInfo(const UIFrontend* frontend) const abstract;

	//Translates figure constraints by dx and dy
	virtual void Translate(int dx, int dy) abstract;

	//Resize figure using node
	virtual void Resize(FigureNode* targetNode) abstract;

	//Returns the absolute position of the figure, could be one of the vertices or just the center
	virtual Point GetPosition() abstract;

	//Returns the shape as an enum value
	virtual DWShape GetShape() abstract;

	//Saves the figure
	virtual void Save(Serializer* serializer) abstract;

	//Loads the figure data
	virtual void Load(Deserializer* deserializer) abstract;
};

//forward declaration
class Application;

//returns a pointer to Application
extern Application* GetApplication();