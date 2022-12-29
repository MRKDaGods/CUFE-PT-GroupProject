#include "Action.h"
#include "../Application.h"

Action::Action(Application* app)
{
	m_Application = app;

	m_Output = m_Application->GetOutput();
	m_Input = m_Application->GetInput();
	m_Frontend = m_Application->GetUIFrontend();
}
