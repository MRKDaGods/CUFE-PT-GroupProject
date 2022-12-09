#include "Common.h"

#ifdef TEST_MODE

#include "Core/Application.h"

//This is a test code to test the Input and Output classes

//Define application pointer
Application* pApp = 0;

//Returns a pointer to Application
Application* GetApplication()
{
	return pApp;
}

int main()
{
	int x,y;

	pApp = new Application;

	//manually render initially
	pApp->Render();

	//Create Input and Output objects to test
	Output* pOut = pApp->GetOutput();
	Input* pIn = pApp->GetInput();

	//Starting the test
	pOut->PrintMessage("This demo is to test input and output classes, Click anywhere to start the test");
	pIn->GetPointClicked(x,y);	//Wait for any click

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 1:	
	//			Create The FULL Tool bar, the drawing area and the status bar	
	//			This has already been done through the constrcutor of class Output
	///////////////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("TEST1: Drawing Tool bar and Status bar, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	
	///////////////////////////////////////////////////////////////////////////////////
	// TEST 2:	
	//			Drawing all the Figures with all possible states: 
	//			Non-filled, Filled, and highlighted in both cases			
	///////////////////////////////////////////////////////////////////////////////////
	
	pOut->PrintMessage("TEST2: Now we will show that Output class can draw any figure in any state, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	GfxInfo* gfxInfo = pApp->GetGfxInfo();//to be used with draw function of the class Ouput
	Point P1, P2, P3;

	/// 2.1- Rectangle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Rectangle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	///////////////////////////////////////////////////////////
	
	// 2.1.1 - Drawing non-filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> non-filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);

	gfxInfo->border_width = 5;
	gfxInfo->draw_col = BLACK;	//any color for border
	gfxInfo->is_filled = false;	//Figure is NOT filled
	pOut->DrawRectangle(P1, P2, false);

	// 2.1.2 - Drawing highlighted non-filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->DrawRectangle(P1, P2, true);


	// 2.1.3 - Drawing a filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);

	gfxInfo->border_width = 6;
	gfxInfo->draw_col = BLUE;	//any color for border
	gfxInfo->fill_col = GREEN;//any color for filling
	gfxInfo->is_filled = true;//Figure is filled
	pOut->DrawRectangle(P1, P2, false);


	// 2.1.4 - Drawing a highlighted filled rectangle
	pOut->PrintMessage("Drawing a Rectangle ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->DrawRectangle(P1, P2, true);

	///////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("Drawing a Rectangle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();

	/// 2.2- Square Test ///
	/// ============== 
	pOut->PrintMessage("Drawing a Square, normal and Highlighted, Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	////////////////////////////////////////////////////////

	// 2.2.1 - Drawing non-filled square
	pOut->PrintMessage("Drawing a Square ==> non-filled, Click a point");
	pIn->GetPointClicked(P1.x, P1.y);

	gfxInfo->border_width = 5;
	gfxInfo->draw_col = BLACK;	//any color for border
	gfxInfo->is_filled = false;	//Figure is NOT filled
	pOut->DrawSquare(P1, false);

	// 2.2.2 - Drawing highlighted non-filled square
	pOut->PrintMessage("Drawing a Square ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawSquare(P1, true);


	// 2.2.3 - Drawing a filled square
	pOut->PrintMessage("Drawing a Square ==> filled,  Click a point");
	pIn->GetPointClicked(P1.x, P1.y);

	gfxInfo->border_width = 6;
	gfxInfo->draw_col = BLUE;	//any color for border
	gfxInfo->fill_col = GREEN;//any color for filling
	gfxInfo->is_filled = true;//Figure is filled
	pOut->DrawSquare(P1, false);


	// 2.2.4 - Drawing a highlighted filled square
	pOut->PrintMessage("Drawing a Square ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawSquare(P1, true);

	////////////////////////////////////////////////////////

	pOut->PrintMessage("Drawing a Square Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();

	/// 2.3- Triangle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Triangle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	///////////////////////////////////////////////////////////////////////////////

	// 2.3.1 - Drawing non-filled triangle
	pOut->PrintMessage("Drawing a Triangle ==> non-filled,  Click three points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->GetPointClicked(P3.x, P3.y);

	gfxInfo->border_width = 5;
	gfxInfo->draw_col = BLACK;	//any color for border
	gfxInfo->is_filled = false;	//Figure is NOT filled
	pOut->DrawTriangle(P1, P2, P3, false);

	// 2.3.2 - Drawing highlighted non-filled triangle
	pOut->PrintMessage("Drawing a Triangle ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawTriangle(P1, P2, P3, true);


	// 2.3.3 - Drawing a filled triangle
	pOut->PrintMessage("Drawing a Triangle ==> filled,  Click three points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->GetPointClicked(P3.x, P3.y);

	gfxInfo->border_width = 6;
	gfxInfo->draw_col = BLUE;	//any color for border
	gfxInfo->fill_col = GREEN;//any color for filling
	gfxInfo->is_filled = true;//Figure is filled
	pOut->DrawTriangle(P1, P2, P3, false);


	// 2.3.4 - Drawing a highlighted filled triangle
	pOut->PrintMessage("Drawing a Triangle ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawTriangle(P1, P2, P3, true);

	///////////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("Drawing a Triangle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();
	
	/// 2.4- Hexagon Test ///
	/// =================== 
	pOut->PrintMessage("Drawing a Hexagon, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	////////////////////////////////////////////////////////

	// 2.4.1 - Drawing non-filled hexagon
	pOut->PrintMessage("Drawing a Hexagon ==> non-filled, Click a point");
	pIn->GetPointClicked(P1.x, P1.y);

	gfxInfo->border_width = 5;
	gfxInfo->draw_col = BLACK;	//any color for border
	gfxInfo->is_filled = false;	//Figure is NOT filled
	pOut->DrawHexagon(P1, false);

	// 2.4.2 - Drawing highlighted non-filled hexagon
	pOut->PrintMessage("Drawing a Hexagon ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawHexagon(P1, true);


	// 2.4.3 - Drawing a filled hexagon
	pOut->PrintMessage("Drawing a Hexagon ==> filled,  Click a point");
	pIn->GetPointClicked(P1.x, P1.y);

	gfxInfo->border_width = 6;
	gfxInfo->draw_col = BLUE;	//any color for border
	gfxInfo->fill_col = GREEN;//any color for filling
	gfxInfo->is_filled = true;//Figure is filled
	pOut->DrawHexagon(P1, false);


	// 2.4.4 - Drawing a highlighted filled hexagon
	pOut->PrintMessage("Drawing a Hexagon ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawHexagon(P1, true);

	////////////////////////////////////////////////////////

	pOut->PrintMessage("Drawing a Hexagon Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();
	
	/// 2.5- Circle Test ///
	/// =================== 
	pOut->PrintMessage("Drawing an Circle, filled/non-filled and Highlighted filled/non-filled,  Click to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click

	///////////////////////////////////////////////////////////

	// 2.5.1 - Drawing non-filled circle
	pOut->PrintMessage("Drawing a Circle ==> non-filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);

	gfxInfo->border_width = 5;
	gfxInfo->draw_col = BLACK;	//any color for border
	gfxInfo->is_filled = false;	//Figure is NOT filled
	pOut->DrawCircle(P1, P2, false);

	// 2.5.2 - Drawing highlighted non-filled circle
	pOut->PrintMessage("Drawing a Circle ==> Highlighted non-filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawCircle(P1, P2, true);


	// 2.5.3 - Drawing a filled circle
	pOut->PrintMessage("Drawing a Circle ==> filled,  Click two points");
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->GetPointClicked(P2.x, P2.y);

	gfxInfo->border_width = 6;
	gfxInfo->draw_col = BLUE;	//any color for border
	gfxInfo->fill_col = GREEN;//any color for filling
	gfxInfo->is_filled = true;//Figure is filled
	pOut->DrawCircle(P1, P2, false);


	// 2.5.4 - Drawing a highlighted filled circle
	pOut->PrintMessage("Drawing a Circle ==> Highlighted filled, Click to Highlight");
	pIn->GetPointClicked(x, y);	//Wait for any click
	pOut->DrawCircle(P1, P2, true);

	///////////////////////////////////////////////////////////////////////////

	pOut->PrintMessage("Drawing a Circle Test ==> OK,  Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();
	
	///////////////////////////////////////////////////////////////////////////////////
	// TEST 3: 
	//			Input Class: Read strings from the user
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST3: Now Time to test class Input, Click anywhere to continue");
	pIn->GetPointClicked(x,y);	//Wait for any click
	
	pOut->PrintMessage("Testing Input ability to read strings");

	///TODO: Add code here to 
	// 1- Read a string from the user on the status bar
	// 2- After reading the string clear the status bar
	// 3- print on the status bar "You Entered" then print the string

	string str = pIn->GetString(pOut);
	pOut->PrintMessage("You Entered: " + str);

	pIn->GetPointClicked(x,y);	//Wait for any click
	pOut->ClearDrawArea();

	///////////////////////////////////////////////////////////////////////////////////
	// TEST 4: 
	//			Input Class : Check for the user action
	///////////////////////////////////////////////////////////////////////////////////
	pOut->PrintMessage("TEST4: Testing Input ability to detect User Action, click anywhere");
	
	//This handles all the actions
	while (pApp->IsRunning())
	{
		pApp->Loop();
		Sleep(1000 / TARGET_FPS);
	}

	/// Exiting
	pOut->PrintMessage("Action: EXIT, test is finished, click anywhere to exit");
	pIn->GetPointClicked(x,y);

	delete pApp;

	return 0;
}


#endif