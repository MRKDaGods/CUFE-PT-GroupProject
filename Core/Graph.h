#pragma once

#include <string>

class Application;

class Graph
{
private:
	Application* m_Application;
	std::string m_TempFilename;

public:
	Graph(Application* app);
	~Graph();

	//Backs up the graph to a temporary file
	void Backup();

	//Restores a previously saved graph in this session
	void Restore();
};