#include "AddAssignOperator.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddAssignOperator::AddAssignOperator(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddAssignOperator::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Value Assignment Statement: Click to add the statement");

	pIn->GetPointClicked(Position);
	while (!(Position.x <UI.DrawingAreaWidth && Position.y >UI.ToolBarHeight && Position.y < (UI.height - UI.StatusBarHeight))) {
		(pManager->GetOutput())->PrintMessage("You Should Draw in the Drawing Area Only, Click anywhere in the Drawing Area");
		pIn->GetPointClicked(Position);
	}
	while ((pManager->GetStatement(Position))) {
		(pManager->GetOutput())->PrintMessage("You cannot Put Statement Above The other , click anywhere else");
		pIn->GetPointClicked(Position);
	}
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bapr to enter the LHS and set the data member
	pOut->PrintMessage("Please Enter Left Hand Side");
	LHS = pIn->GetVariabel(pOut);

	
	//ValueOrVariable()
	pOut->PrintMessage("Please Enter First Operand Right Hand Side ");
	RHS_1 = pIn->GetVariabelOrValue(pOut);

	pOut->PrintMessage("Please Enter Operator ");
	op = pIn->GetArithOperator(pOut);

	pOut->PrintMessage("Please Enter Second Operand Right Hand Side ");
	RHS_2 = pIn->GetVariabelOrValue(pOut);
	
	//TODO: Ask the user in the status bar to enter the RHS and set the data member

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddAssignOperator::Execute()
{
	ReadActionParameters();

	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	AssignOperator* pAssign = new AssignOperator(Corner, LHS, RHS_1,op,RHS_2);
	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pAssign); // Adds the created statement to application manger's statement list
}

