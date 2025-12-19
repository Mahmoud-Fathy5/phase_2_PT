#include "AddWrite.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"




//constructor: set the ApplicationManager pointer inside this action
AddWrite::AddWrite(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddWrite::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Write the (Position) parameter
	pOut->PrintMessage("Write Statement: Click to Add a Write Statement");

	pIn->GetPointClicked(Position);
	while (!(Position.x <UI.DrawingAreaWidth && Position.y >UI.ToolBarHeight && Position.y < (UI.height - UI.StatusBarHeight))) {
		(pManager->GetOutput())->PrintMessage("You Should Draw in the Drawing Area Only, Click anywhere in the Drawing Area");
		pIn->GetPointClicked(Position);
	}
	//while ((pManager->GetStatement(Position))) {
		//(pManager->GetOutput())->PrintMessage("You cannot Put Statement Above The other , click anywhere else");
		//pIn->GetPointClicked(Position);
	//}
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bapr to enter the LHS and set the data member
	pOut->PrintMessage("Please Enter Variable name or String");
	VarOrValu = pIn->GetStringlOrVariable(pOut);

	//TODO: Ask the user in the status bar to enter the RHS and set the data member

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddWrite::Execute()
{
	ReadActionParameters();
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;   // need to be considerdddd
	Corner.y = Position.y;

	Write* pWrite = new Write(Corner, VarOrValu);
	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in WriteActionParameters()

	pManager->AddStatement(pWrite); // Adds the created statement to application manger's statement list
}

