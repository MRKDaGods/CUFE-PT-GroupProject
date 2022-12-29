#pragma once

#include "../DEFS.h"
#include "../GUI/Output.h"

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

	virtual void Draw(Output* pOut) const abstract;		//Draw the figure

	void ChangeDrawColor(color Dclr);	//changes the figure's drawing color
	void ChangeFillColor(color Fclr);	//changes the figure's filling color

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	//virtual void Save(ofstream &OutFile) = 0;	//Save the figure parameters to the file
	//virtual void Load(ifstream &Infile) = 0;	//Load the figure parameters to the file

	//virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar
};