#pragma once

#include "../Action.h"

class CFigure;

class ActionDelete : public Action
{
private:
	CFigure* m_DeletedFigure;
	int m_DeletedFigureID;

public:
	ActionDelete(Application* app);
	~ActionDelete();

	virtual void ReadActionParameters() override;
	virtual void Execute() override;
	virtual void Undo() override;
	virtual ActionType GetActionType() override;
};