#ifndef OUPTUT_H
#define OUPTUT_H

#include "Input.h"
#include "../Utils/Rect.h"
#include "../Utils/Color.h"

class Output	//The application manager should have a pointer to this class
{
private:	
	window* pWind;	//Pointer to the Graphics Window
	void* m_App; //Pointer to Application, avoid cyclic header, declare as void*


	//Returns the gfx info from Application
	GfxInfo* GetGfxInfo() const;

	//Prepares the graphics info for rendering the next figure, and returns the draw style
	drawstyle PrepareFigureRendering(bool selected, GfxInfo** callerGfx = 0) const;

public:
	Output(void* app);		

	window* CreateWind(int, int, int , int) const; //creates the application window
	void CreateStatusBar() const;	//create the status bar

	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area

	// -- FRONTEND related --
	//Clears a specified region
	void ClearArea(Rect rect) const;

	//Draws an image of specified rect and path
	void DrawImage(Rect rect, string path);

	//Draws a filled rect
	void DrawRect(Rect rect, Color color, bool filled = true, int width = 1);

	void DrawLine(Vector2 p1, Vector2 p2, int w, Color color);

	void DrawString(Rect rect, string msg, int fontSz);
	
	// -- Figures Drawing functions

	//Draw a rectangle from top left and bottom right points
	void DrawRectangle(Point topLeft, Point botRight, bool selected = false) const;

	//Draw a square from given center
	void DrawSquare(Point center, bool selected = false) const;

	//Draw a triangle from 3 vertices
	void DrawTriangle(Point v1, Point v2, Point v3, bool selected = false) const;

	//Draw a hexagon from given center
	void DrawHexagon(Point center, bool selected = false) const;

	//Draw a circle from given center and a point on the circumference
	void DrawCircle(Point center, Point radiusPoint, bool selected = false, int* outRadius = 0) const;
	
	//Print a message on Status bar
	void PrintMessage(string msg) const;

	color getCrntDrawColor() const;	//get current drwawing color
	color getCrntFillColor() const;	//get current filling color
	int getCrntPenWidth() const;		//get current pen width
	
	~Output();
};

#endif