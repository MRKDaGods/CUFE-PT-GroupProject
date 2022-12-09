#include "Common.h"

#ifndef TEST_MODE

#include "Core/Application.h"

//Define application pointer
Application* pApp = 0;

//Entrypoint
int main() 
{
	//TODO: Only invalidate regions that need to be redrawn rather than the whole buffer
	// due to latency
	//declare app
	pApp = new Application;

	//manually render initially
	pApp->Render();

	while (pApp->IsRunning())
	{
		pApp->Loop();
		Sleep(1000 / TARGET_FPS);
	}

	delete pApp;

	return 0;
}

//Returns a pointer to Application
Application* GetApplication()
{
	return pApp;
}

#endif