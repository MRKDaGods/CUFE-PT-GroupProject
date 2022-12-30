#include "ActionLoad.h"
#include "../../Application.h"
#include "../../Deserializer.h"
#include "../../../Figures/CCircle.h"
#include "../../../Figures/CHexagon.h"
#include "../../../Figures/CRectangle.h"
#include "../../../Figures/CSquare.h"
#include "../../../Figures/CTriangle.h"

#include <fstream>

ActionLoad::ActionLoad(Application* app) : Action(app)
{
	m_Filename = "";
}

void ActionLoad::ReadActionParameters()
{
	m_Frontend->SetStatusBarText("LOAD: Enter filename");

	//get filename
	m_Filename = m_Input->GetString(m_Output);

	m_Frontend->SetStatusBarText("");
}

void ActionLoad::Execute()
{
	//define deserializer with our filename
	Deserializer d(m_Filename);

	//check if exists
	if (!d.Valid())
	{
		//file doesnt exist
		m_Frontend->SetStatusBarText("LOAD: Cannot load graph, " + m_Filename + "does not exist");
		d.Close();
		return;
	}

	//clear everything
	//taken from ActionClearAll
	m_Frontend->Reset();

	//delete all figures
	m_Application->DeleteAllFigures();

	//set selected figure to null
	m_Application->SetSelectedFigure(0);

	//clear history
	m_Application->GetActionHistory()->Clear();

	//now read graph data

	//the global gfx info
	GfxInfo* gfx = m_Application->GetGfxInfo();

	//draw color
	color drawCol = d.ReadColor();
	DWColors frontendDrawColor = NativeToFrontendColor(drawCol);

	gfx->draw_col = drawCol;
	m_Frontend->SetSelectedColor(frontendDrawColor);

	//fill color
	color fillCol = d.ReadColor();
	gfx->fill_col = drawCol;

	//figure count
	int figCount = d.Read<int>();

	//read figures
	for (int i = 0; i < figCount; i++)
	{
		//get figure type
		DWShape shape = (DWShape)d.Read<int>();

		//declare figure
		CFigure* fig = 0;

		//now create figure according to shape
		switch (shape)
		{
		case DWSHAPE_RECTANGLE:
			fig = new CRectangle(*gfx);
			break;

		case DWSHAPE_SQUARE:
			fig = new CSquare(*gfx);
			break;

		case DWSHAPE_TRIANGLE:
			fig = new CTriangle(*gfx);
			break;

		case DWSHAPE_HEXAGON:
			fig = new CHexagon(*gfx);
			break;

		case DWSHAPE_CIRCLE:
			fig = new CCircle(*gfx);
			break;

		case DWSHAPE_COUNT:
			break;
		}

		//if fig is null then graph isnt valid obviously
		if (fig == 0)
		{
			m_Frontend->SetStatusBarText("LOAD: Invalid grpah");
			d.Close();
			return;
		}

		//load figure data
		fig->Load(&d);

		//add figure to figlist, but dont update interface
		m_Application->AddFigure(fig, false, false);
	}

	//load done, close stream
	d.Close();

	//update interface after everything has been loaded
	m_Application->Render(true);
}

ActionType ActionLoad::GetActionType()
{
	return ACTION_DRAW_OTHER_OPEN_GRAPH;
}
