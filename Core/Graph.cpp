#include "Graph.h"
#include "Application.h"
#include "Actions/Other/ActionSave.h"
#include "Actions/Other/ActionLoad.h"

Graph::Graph(Application* app)
{
	m_Application = app;

	//generate a temp filename to use for this session
	m_TempFilename = "__temp_" + std::to_string(rand());
}

Graph::~Graph()
{
	//delete temp file if exists
	remove(m_TempFilename.c_str());
}

void Graph::Backup()
{
	//invoke the save action with our temp filename
	Action* save = new ActionSave(m_Application, m_TempFilename);
	save->Execute();

	//delete action
	delete save;
}

void Graph::Restore()
{
	//invoke the load action with our temp filename, it simply fails if not saved before
	Action* load = new ActionLoad(m_Application, m_TempFilename);
	load->Execute();

	//delete action
	delete load;
}
