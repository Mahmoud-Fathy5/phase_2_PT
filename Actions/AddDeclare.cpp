#include "AddDeclare.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddDeclare::AddDeclare(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddDeclare::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Declare Statement: Click to declare a Variabel");

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

	pOut->PrintMessage("Please Enter varaiable");
	var = pIn->GetVariabel(pOut);

}

void AddDeclare::Execute()
{
	ReadActionParameters();

	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;
	Corner.y = Position.y;

	Declare* pDeclare = new Declare(Corner, var);
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pDeclare); // Adds the created statement to application manger's statement list
}
