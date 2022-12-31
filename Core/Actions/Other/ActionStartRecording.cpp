#include "ActionStartRecording.h"
#include "../../Application.h"

ActionStartRecording::ActionStartRecording(Application* app) : Action(app)
{
}

void ActionStartRecording::ReadActionParameters()
{
}

void ActionStartRecording::Execute()
{
    //so we can only record, if the last action executed is null (no actions have been exe'd before)
    //or last action is clear all
    Action* lastAction = m_Application->GetActionHistory()->GetLastAction();
    if (lastAction != 0 && lastAction->GetActionType() != ACTION_DRAW_OTHER_CLEAR_ALL)
    {
        m_Frontend->SetStatusBarText("RECORDING: Cannot start recording");
        return;
    }

    //start recording
    m_Application->GetRecorder()->SetRecording(true);

    //display rec label
    m_Frontend->SetRecording(true);

    m_Frontend->SetStatusBarText("RECORDING: Started recording");
}

ActionType ActionStartRecording::GetActionType()
{
    return ACTION_DRAW_OTHER_REC_START;
}
