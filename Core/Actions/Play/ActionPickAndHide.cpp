#include "ActionPickAndHide.h"
#include "../../Application.h"

ActionPickAndHide::ActionPickAndHide(Application* app, PMPickHide pickHideMode) : Action(app)
{
    m_Mode = pickHideMode;

    //dummy initials
    //set to ENUM_COUNT to catch errors easily later on
    m_TargetShape = DWSHAPE_COUNT;
    m_TargetColor = DWCOLOR_COUNT;

    //init score to 0
    m_Incorrect = 0;
    m_Correct = 0;

    m_MaxGrade = 0;
}

void ActionPickAndHide::InitGameData()
{
    //determine what to init
    switch (m_Mode)
    {
    case PMPICKHIDE_FIG_TYPE:
        m_Application->GetDistinctFiguresInfo(0, &m_Shapes);

        //choose a random shape
        m_TargetShape = m_Shapes[rand() % m_Shapes.size()];

        //get max grade
        m_MaxGrade = m_Application->GetFigureCountWithShape(m_TargetShape);

        //get game title
        m_GameTitle = ShapeToString(m_TargetShape);
        break;

    case PMPICKHIDE_FIG_COL:
        m_Application->GetDistinctFiguresInfo(&m_Colors, 0);

        //choose a random color
        m_TargetColor = m_Colors[rand() % m_Colors.size()];

        //get max grade
        m_MaxGrade = m_Application->GetFigureCountWithColor(m_TargetColor);

        //get game title
        m_GameTitle = ColorToString(m_TargetColor);
        break;

    case PMPICKHIDE_FIG_TYPE_COL:
        m_Application->GetDistinctFiguresInfo(0, &m_Shapes);

        //choose a random shape
        m_TargetShape = m_Shapes[rand() % m_Shapes.size()];

        //and then accordingly choose the color
        m_TargetColor = m_Application->GetRandomColorForShape(m_TargetShape);

        //get max grade
        m_MaxGrade = m_Application->GetFigureCountWithShapeAndColor(m_TargetShape, m_TargetColor);

        //get game title
        m_GameTitle = ColorToString(m_TargetColor) + " " + ShapeToString(m_TargetShape);
        break;

    default:
        break;
    }
}

bool ActionPickAndHide::FigureMeetsRequirements(CFigure* fig)
{
    if (fig == 0) return false;

    switch (m_Mode)
    {
    case PMPICKHIDE_FIG_TYPE:
        return fig->GetShape() == m_TargetShape;

    case PMPICKHIDE_FIG_COL:
        return fig->GetGfxInfo()->fill_col == m_TargetColor;

    case PMPICKHIDE_FIG_TYPE_COL:
        return fig->GetShape() == m_TargetShape && fig->GetGfxInfo()->fill_col == m_TargetColor;

    default:
        break;
    }

    return false;
}

std::string ActionPickAndHide::ShapeToString(DWShape shape)
{
    switch (shape)
    {
    case DWSHAPE_RECTANGLE:
        return "RECTANGLE";

    case DWSHAPE_SQUARE:
        return "SQUARE";

    case DWSHAPE_TRIANGLE:
        return "TRIANGLE";

    case DWSHAPE_HEXAGON:
        return "HEXAGON";

    case DWSHAPE_CIRCLE:
        return "CIRCLE";

    default:
        break;
    }

    return "";
}

std::string ActionPickAndHide::ColorToString(color col)
{
    //convert to frontend color so we can use it in a switch
    switch (NativeToFrontendColor(col))
    {
    case DWCOLOR_BLACK:
        return "BLACK";

    case DWCOLOR_YELLOW:
        return "YELLOW";

    case DWCOLOR_ORANGE:
        return "ORANGE";

    case DWCOLOR_RED:
        return "RED";

    case DWCOLOR_GREEN:
        return "GREEN";

    case DWCOLOR_BLUE:
        return "BLUE";

    default:
        break;
    }

    return "";
}

void ActionPickAndHide::ReadActionParameters()
{
    //for now we wont read anything from the user?
}

void ActionPickAndHide::Execute()
{
    //so first of all, restore the graph, we want it brand new :)
    m_Application->GetGraph()->Restore();

    //if there are no figures, dont continue
    if (m_Application->GetFigureCount() == 0)
    {
        m_Frontend->SetStatusBarText("PICK AND HIDE: No shapes, cannot start game");
        return;
    }

    //graph restored, now init
    InitGameData();

    //game's running as long as total score is less than max grade
    while (m_Correct + m_Incorrect < m_MaxGrade)
    {
        char buf[100];
        sprintf(buf, "PICK AND HIDE: Pick all %sS  Incorrect: %d  Correct: %d  Tries left: %d", 
            m_GameTitle.c_str(), m_Incorrect, m_Correct, m_MaxGrade - (m_Incorrect + m_Correct));

        //update status bar text
        m_Frontend->SetStatusBarText(buf);

        //get click
        Point p;
        m_Input->GetPointClicked(p.x, p.y);

        //now try and find figure with that point
        CFigure* fig = m_Application->GetFigure(p.x, p.y);

        //check if fig is null, if so skip
        if (fig == 0) continue;

        //check if figure meets the requirements
        if (FigureMeetsRequirements(fig))
        {
            //yay, increase score
            m_Correct++;
        }
        else
        {
            //wrong choice :(
            m_Incorrect++;
        }

        //hide figure
        m_Application->DeleteFigure(fig);

        //update screen
        m_Application->Render(true);
    }

    //game ended
    //calculate percent
    float percent = m_Correct / (float)m_MaxGrade * 100.0f;

    //print overview
    char fbuf[100];
    sprintf(fbuf, "PICK AND HIDE: GAME OVER  Incorrect: %d  Correct: %d  Grade: %.0f%%", m_Incorrect, m_Correct, percent);
    m_Frontend->SetStatusBarText(fbuf);
}

ActionType ActionPickAndHide::GetActionType()
{
    switch (m_Mode)
    {
    case PMPICKHIDE_FIG_TYPE:
        return ACTION_PLAY_PICKHIDE_FIGTYPE;

    case PMPICKHIDE_FIG_COL:
        return ACTION_PLAY_PICKHIDE_FIGCOL;

    case PMPICKHIDE_FIG_TYPE_COL:
        return ACTION_PLAY_PICKHIDE_FIGTYPE_COL;

    case PMPICKHIDE_COUNT:
        return ACTION_PLAY_PICKHIDE_BEGIN;
    }
}
