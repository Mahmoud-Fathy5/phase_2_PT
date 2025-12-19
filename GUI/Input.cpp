
#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(Point &P) const
{
	pWind->WaitMouseClick(P.x, P.y);	//Wait for mouse click
}

string Input::GetString(Output *pO) const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}


double Input::GetValue(Output* pO) const	// Reads a double value from the user 
{	
	///TODO: add code to read a double value from the user and assign it to D

	string value;


	double D = 0;
	value=GetString(pO);

	while (!(IsValue(value)))
	{
		pO->PrintMessage("Please enter a valid double value");
		value=GetString(pO);
	}
	D = stod(value);
	
		
	//This function should make any needed validations on the entered text 
	// to make sure it is a double value (e.g. 12.5, -12.5, -23, -23., -23.0 …etc.).

	
	
	//Read a double value from the user
	
	return D;
}


//TODO: Add the function Input::GetVariable 
// to read a “variable name” from the user (from the keyboard). 
// It does not return before taking a valid variable name.

string Input::GetVariabel(Output *pO)const
{
	string variabel;
	variabel = GetString(pO);
	while (!(IsVariable(variabel)))
	{
		pO->PrintMessage("Please Enter a valid variabel name");
		variabel = GetString(pO);
		
	}
	return variabel;
}



//TODO: Add the function Input::GetArithOperator 
// to read an arithmetic operator (+, -, * or /) from the user. 
// It does not return before taking a valid arithmetic operator.
string Input::GetArithOperator(Output* pO)const
{
	string arithmetic_operator;
	arithmetic_operator = GetString(pO);
	while (arithmetic_operator != "+" && arithmetic_operator != "-" && arithmetic_operator != "*" && arithmetic_operator != "/")
	{
		pO->PrintMessage("Please Enter a valid arithmetic operator");
		arithmetic_operator = GetString(pO);
	}
	return arithmetic_operator;
}
//TODO: Add the function Input::GetCompOperator
// similar to the previous function but for comparison operators (==, !=, <, <=, > or >=).

string Input::GetCompOperator(Output* pO)const
{
	string comparison_operator;
	comparison_operator = GetString(pO);
	while (comparison_operator != "==" && comparison_operator != ">" && comparison_operator != "<" && comparison_operator != ">="&& comparison_operator != "<="&& comparison_operator != "!=")
	{
		pO->PrintMessage("Please Enter a valid comparison operator");
		comparison_operator = GetString(pO);
	}
	return comparison_operator;
}

string Input::GetVariabelOrValue(Output* pO) const
{
	string ValOrVar=GetString(pO);
	while (ValueOrVariable(ValOrVar) == INVALID_OP) {
		pO->PrintMessage("Please Enter a Valid Operand");
		ValOrVar = GetString(pO);
	}
	return ValOrVar;
}

string Input::GetStringlOrVariable(Output* pO) const
{
	string S_or_V;
	S_or_V = GetString(pO);
	while (!(IsVariable(S_or_V)) && !(IsStrring(S_or_V))) {
		pO->PrintMessage("Please Enter a valid variabel name or String");
		S_or_V = GetString(pO);
	}
	pO->ClearStatusBar();
	return S_or_V;
	return string();
}



//TODO: Complete the implementation of the following function
ActionType Input::GetUserAction() const
{
	//This function reads the position where the user clicks to determine the desired action

	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.AppMode == DESIGN)	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//This assumes that menu items are lined up horizontally
			int ClickedItem = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on
			switch (ClickedItem)
			{
			case ITM_START:return ADD_START;
			case ITM_READ:return ADD_READ;
			case ITM_WRITE:return ADD_WRITE;
			case ITM_DECLARE: return ADD_DECLARE_VARIABLE;
			case ITM_VALUE_ASSIGN:return ADD_VALUE_ASSIGN;
			case ITM_VAR_ASSIGN:return ADD_VAR_ASSIGN;
			case ITM_OPER_ASSIGN:return  ADD_OPER_ASSIGN;
			case ITM_COND:return ADD_CONDITION;
			case ITM_END:return ADD_END;
			case ITM_CONNECTOR:return ADD_CONNECTOR;
			case ITM_DELETE:return DEL;
			case ITM_SWITCH_SIM:return SWITCH_SIM_MODE;
			case ITM_SELECT:return SELECT;
			case ITM_EDIT:return EDIT_STAT;
			case ITM_COPY:return COPY;
			case ITM_PASTE:return PASTE;
			case ITM_CUT:return CUT;
			case ITM_SAVE:return SAVE;
			case ITM_LOAD:return LOAD;
			case ITM_EXIT:return EXIT;
			default: return DSN_TOOL;
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;
			else
				return OUTPUT_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//Application is in Simulation mode
	{

		// TODO: This should be changed after creating the compelete simulation bar 
		//return SWITCH_DSN_MODE;	// THIS SHOULD BE CHANGED
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItem = (x / UI.MenuItemWidth);
			switch (ClickedItem)
			{
			case ITM_RUN: return RUN;
			case ITM_VALIDATE: return VALIDATE;
			case ITM_SWITCH_DSN: return SWITCH_DSN_MODE;
			case ITM_GENERATE_CODE: return GENERATE_CODE;
			case ITM_DEBUG: return DEBUG;
			case ITM_EXIT_SIM: return EXIT;
			default: return SIM_TOOL;
			}
		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (x <= UI.DrawingAreaWidth)
				return DRAWING_AREA;
			else
				return OUTPUT_AREA;
		}
		return STATUS;
	}

}


Input::~Input()
{
}
