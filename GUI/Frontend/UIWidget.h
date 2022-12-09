#pragma once

#include <vector>

#include "../../Utils/Vector2.h"
#include "../../Utils/Rect.h"
#include "UITouchEvent.h"

//Anchor preference for widget
enum class UIAnchor 
{
    None = 0,

    Top = 1,
    Middle = 2,
    Bottom = 4,

    Left = 8,
    Center = 16,
    Right = 32,

    TopLeft = Top | Left,
    TopCenter = Top | Center,
    TopRight = Top | Right,

    MiddleLeft = Middle | Left,
    MiddleCentre = Middle | Center,
    MiddleRight = Middle | Right,

    BottomLeft = Bottom | Left,
    BottomCenter = Bottom | Center,
    BottomRight = Bottom | Right
};

enum class UIWidgetType
{
    None,
    Display,
    Window,
    Button,
    Label,
    Toggle,
    Sprite,
    ShapeList,
    LineRenderer
};

int operator&(UIAnchor right, UIAnchor left);
UIAnchor operator|(UIAnchor right, UIAnchor left);

class UIWidget
{
protected:
    Vector2 m_Position;
    Vector2 m_Size;
    bool m_Visible;
    bool m_Focused;
    std::vector<UIWidget*> m_Children;

    void ClearArea();
    void NotifyConstraintChanged();

    //forces the component/screen to render
    void Invalidate();

private:
    UIAnchor m_Anchor;
    UIWidget* m_Parent;
    Rect m_Rect;
    bool m_DontHandleTouch;
    UIWidgetType m_Type;

    void RecalculateAnchors();

public:
    UIWidget(UIWidget* parent, UIAnchor anchor, Rect rect, UIWidgetType type);
    ~UIWidget();
    UIWidget* FindWidget(Vector2 pos);
    void UpdateFocusState(bool focused, bool withChildren = true);
    virtual bool HandleTouchEvent(UITouchEvent* evt);
    virtual void Draw();
    void SetVisible(bool visible, bool invokeDirty = true);
    Vector2 Position();
    bool Visible();
    bool DontHandleTouch();
    void SetDontHandleTouch(bool val);
    Rect ScreenRect();
    void AddChild(UIWidget* child);
    UIWidgetType Type();
};

//forward declaration
class Application;

//returns a pointer to Application
extern Application* GetApplication();