#pragma once

#include "../Common.h"
#include "../DEFS.h"
#include "../GUI/Output.h"
#include "../Core/Serializer.h"
#include "../Core/Deserializer.h"

class UIFrontend;

//Base class for all figures
class CFigure
{
protected:
	int m_ID;
	bool m_Selected;
	GfxInfo m_GfxInfo;

public:
	CFigure(GfxInfo gfxInfo);

	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected

	GfxInfo* GetGfxInfo();

	virtual void Draw(Output* pOut) const abstract;		//Draw the figure

	void ChangeDrawColor(color Dclr);	//changes the figure's drawing color
	void ChangeFillColor(color Fclr);	//changes the figure's filling color

	virtual bool HitTest(Point hit) abstract;
	virtual void PrintInfo(const UIFrontend* frontend) const abstract;

	//Translates figure constraints by dx and dy
	virtual void Translate(int dx, int dy) abstract;

	//Resize figure with respect to dx and dy
	virtual void Resize(int dx, int dy) abstract;

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