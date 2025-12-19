#include "AddIf.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddIf::AddIf(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddIf::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Conditional Statement: Click to add the statement");

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
	LHS = pIn->GetVariabelOrValue(pOut);

	pOut->PrintMessage("Please Enter Comparator ");
	op = pIn->GetCompOperator(pOut);


	//ValueOrVariable()
	pOut->PrintMessage("Please Enter Right Hand Side ");
	RHS = pIn->GetVariabelOrValue(pOut);

}

void AddIf::Execute()
{
	ReadActionParameters();

	//Calculating left corner of If statement block
	Point Corner;
	Corner.x = Position.x - UI.COND_WDTH / 2;
	Corner.y = Position.y;

	If* pIf = new If(Corner, LHS, RHS, op);

	pManager->AddStatement(pIf); // Adds the created statement to application manger's statement list
}

