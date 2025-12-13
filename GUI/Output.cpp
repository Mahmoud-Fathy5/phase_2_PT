#include "Output.h"


Output::Output()
{
	//Initialize user interface parameters
	UI.width = 1200;
	UI.height = 620;
	UI.wx = 15;
	UI.wy = 15;

	UI.AppMode = DESIGN;	//Design Mode is the default mode

	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 59;	/*was 50*/
	UI.MenuItemWidth = 59;	/*was 80*/
	UI.DrawingAreaWidth = 0.75 * UI.width;

	UI.DrawColor = DODGERBLUE;
	UI.HighlightColor = RED;
	UI.MsgColor = MIDNIGHTBLUE;

	UI.ASSGN_WDTH = 150;
	UI.ASSGN_HI = 50;
	UI.OVAL_WDTH = 80; 
	UI.OVAL_HI = 50;
	UI.COND_WDTH = 150;
	UI.COND_HI = 50;
	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Programming Techniques Project");

	pWind->SetPen(RED, 3);

	CreateDesignToolBar();
	ClearStatusBar();
	ClearDrawArea();
	ClearOutputBar();
}


Input* Output::CreateInput()
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y)
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar()
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawLine(0, UI.height - UI.StatusBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateDesignToolBar() //Draws the Design Menu
{
	UI.AppMode = DESIGN;	//Design Mode
	ClearToolBar();
	//fill the tool bar 

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in Defs.h ==> enum DrawMenuItem


	string MenuItemImages[DSN_ITM_CNT];
	MenuItemImages[ITM_START] = "images\\start1.jpg";
	MenuItemImages[ITM_READ] = "images\\Read.jpg";
	MenuItemImages[ITM_WRITE] = "images\\Write.jpg";
	MenuItemImages[ITM_DECLARE] = "images\\rounded-rectangle.jpg";
	MenuItemImages[ITM_VALUE_ASSIGN] = "images\\Value_assign.jpg";
	MenuItemImages[ITM_VAR_ASSIGN] = "images\\Var_assign.jpg";
	MenuItemImages[ITM_OPER_ASSIGN] = "images\\Op_assign.jpg";
	MenuItemImages[ITM_COND] = "images\\rhombus.jpg";
	MenuItemImages[ITM_END] = "images\\ending.jpg";
	MenuItemImages[ITM_CONNECTOR] = "images\\right-arrow.jpg";
	MenuItemImages[ITM_DELETE] = "images\\del.jpg";
	MenuItemImages[ITM_SWITCH_SIM] = "images\\sim.jpg";
	MenuItemImages[ITM_SELECT] = "images\\select.jpg";
	MenuItemImages[ITM_EDIT] = "images\\pen.jpg";
	MenuItemImages[ITM_COPY] = "images\\copy.jpg";
	MenuItemImages[ITM_PASTE] = "images\\paste.jpg";
	MenuItemImages[ITM_CUT] = "images\\cut.jpg";
	MenuItemImages[ITM_SAVE] = "images\\save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\load.jpg";
	MenuItemImages[ITM_EXIT] = "images\\exit.jpg";


	//TODO: Prepare images for each menu item and add it to the list

	pWind->SetPen(MIDNIGHTBLUE, 3);
	//Draw menu item one image at a time
	for (int i = 0; i < DSN_ITM_CNT; i++)
	{
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
		//if(i != 0)
		//	pWind->DrawLine((i) * UI.MenuItemWidth, 0, (i) * UI.MenuItemWidth, UI.ToolBarHeight);
	}
	pWind->DrawLine(0, 0, UI.width,0); //line above the toolbar
	//Draw a line under the toolbar
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////
//TODO: Complete this function
void Output::CreateSimulationToolBar() //Draws the Simulation Menu
{
	UI.AppMode = SIMULATION;	//Simulation Mode
	///TODO: add code to create the simulation tool bar
	ClearToolBar();
	string MenuItemImages[SIM_ITM_CNT];
	MenuItemImages[ITM_VALIDATE] = "images\\validate.jpg";
	MenuItemImages[ITM_RUN] = "images\\play.jpg";
	MenuItemImages[ITM_GENERATE_CODE] = "images\\code.jpg";
	MenuItemImages[ITM_DEBUG] = "images\\debug.jpg";
	MenuItemImages[ITM_SWITCH_DSN] = "images\\design.jpg";
	MenuItemImages[ITM_EXIT_SIM] = "images\\exit.jpg";


	for (int i = 0; i < SIM_ITM_CNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->SetPen(MIDNIGHTBLUE, 3);
	pWind->DrawLine(0, 0, UI.width, 0); //line above the toolbar
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight); //line below the toolbar



}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar()
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(MIDNIGHTBLUE, 2);
	pWind->SetBrush(LIGHTBLUE);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearDrawArea()
{
	pWind->SetPen(MIDNIGHTBLUE, 2);
	pWind->SetBrush(LIGHTCYAN);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.DrawingAreaWidth, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearOutputBar()
{
	//Create output bar by drawing a filled rectangle
	pWind->SetPen(MIDNIGHTBLUE, 2);
	pWind->SetBrush(LIGHTSTEELBLUE);
	pWind->DrawRectangle(UI.DrawingAreaWidth, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(iX, iY, Text);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearToolBar()
{
	pWind->SetPen(WHITE, 2);
	pWind->SetBrush(WHITE);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

//======================================================================================//
//								Statements Drawing Functions								//
//======================================================================================//

//Draw assignment statement and write the "Text" on it
void Output::DrawAssign(Point Left, int width, int height, string Text, bool Selected)
{
	pWind->SetBrush(LIGHTSTEELBLUE);

	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	//Draw the statement block rectangle
	pWind->DrawRectangle(Left.x, Left.y, Left.x + width, Left.y + height);

	//Write statement text
	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);
}

//TODO: Add similar functions for drawing all other statements.
//		e.g. DrawDeclareStat(.....), DrawCondtionalStat(......), DrawStart(......), DrawEnd(.......), ...etc
//		Decide the parameters that should be passed to each of them
void Output::Drawstart(Point Left, int width, int height, bool Selected)
{
	pWind->SetBrush(LIGHTSTEELBLUE);

	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color
	pWind->DrawEllipse(Left.x, Left.y, Left.x + width, Left.y + height);

	pWind->SetPen(BLACK, 3);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, "Start");

}
void Output::DrawEnd(Point Left, int width, int height, bool Selected)
{
	pWind->SetBrush(LIGHTSTEELBLUE);

	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color
	pWind->DrawEllipse(Left.x, Left.y, Left.x + width, Left.y + height);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, "End");

}
void Output::DrawCondtional(Point Left, int width, int height, string Text, bool Selected)
{
	pWind->SetBrush(LIGHTSTEELBLUE);

	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color
	int xCor[] = { Left.x + width / 2,Left.x + width,Left.x + width / 2,Left.x };
	int yCor[] = { Left.y,Left.y + height / 2,Left.y + height,Left.y + height / 2 };
	pWind->DrawPolygon(xCor, yCor, 4);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);
	//pWind->DrawString(Left.x + width / 4 - 5, Left.y + height / 3 + 10, Text);


}

void Output::DrawRead(Point Left, int width, int height, string Var, bool Selected)
{
	pWind->SetBrush(LIGHTSTEELBLUE);

	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	const int space = 40;
	string Text = "Read " + Var;
	int xCor[] = { Left.x, Left.x + width,Left.x + width - space,Left.x - space };
	int yCor[] = { Left.y,Left.y,Left.y + height,Left.y + height };
	pWind->DrawPolygon(xCor, yCor, 4);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);

}

void Output::DrawWrite(Point Left, int width, int height, string Var, bool Selected)
{
	pWind->SetBrush(LIGHTSTEELBLUE);

	if (Selected)	//if stat is selected, it should be highlighted
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
	else
		pWind->SetPen(UI.DrawColor, 3);	//use normal color

	const int space = 40;
	string Text = "Write " + Var;
	int xCor[] = { Left.x, Left.x + width,Left.x + width - space,Left.x - space };
	int yCor[] = { Left.y,Left.y,Left.y + height,Left.y + height };
	pWind->DrawPolygon(xCor, yCor, 4);

	pWind->SetPen(BLACK, 2);
	pWind->DrawString(Left.x + width / 4, Left.y + height / 4, Text);

}


//TODO: Add DrawConnector function
void Output::DrawConnector(Point first, Point second, bool Selected)
{
	if (Selected)	//if stat is selected, it should be highlighted
	{
		pWind->SetPen(UI.HighlightColor, 3);	//use highlighting color
		pWind->SetBrush(UI.HighlightColor);
	}
	else
	{
		pWind->SetPen(UI.DrawColor, 3);	//use normal color
		pWind->SetBrush(UI.DrawColor);
	}
	const int TriHeight = 5;
	if (first.y < second.y)
	{
		if (first.x == second.x)
			pWind->DrawLine(first.x, first.y, second.x, second.y);
		else
		{
			pWind->DrawLine(first.x, first.y, second.x, first.y);
			pWind->DrawLine(second.x, first.y, second.x, second.y);
		}
		pWind->DrawTriangle(second.x, second.y,
			second.x + TriHeight, second.y - TriHeight,
			second.x - TriHeight, second.y - TriHeight);
	}
	else if (first.y == second.y)
	{
		pWind->DrawLine(first.x, first.y, second.x, second.y);
		if (first.x < second.x)
			pWind->DrawTriangle(second.x, second.y,
				second.x - TriHeight, second.y + TriHeight,
				second.x - TriHeight, second.y - TriHeight);
		else if (first.x > second.x)
			pWind->DrawTriangle(second.x, second.y,
				second.x + TriHeight, second.y + TriHeight,
				second.x + TriHeight, second.y - TriHeight);
	}
	else if (first.y > second.y)
	{
		if (first.x > second.x)
		{
			pWind->DrawLine(first.x, first.y, first.x + 100, first.y);
			pWind->DrawLine(first.x + 100, first.y, first.x + 100, second.y - 15);
			pWind->DrawLine(first.x + 100, second.y-15, second.x, second.y-15);
			pWind->DrawLine(second.x, second.y - 15, second.x, second.y);
		}
		else if (first.x <= second.x)
		{
			pWind->DrawLine(first.x, first.y, first.x - 100, first.y);
			pWind->DrawLine(first.x - 100, first.y, first.x - 100, second.y-15);
			pWind->DrawLine(first.x - 100, second.y-15, second.x, second.y-15);
			pWind->DrawLine(second.x, second.y - 15, second.x, second.y);
		}
		pWind->DrawTriangle(second.x, second.y,
			second.x + TriHeight, second.y - TriHeight,
			second.x - TriHeight, second.y - TriHeight);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}
