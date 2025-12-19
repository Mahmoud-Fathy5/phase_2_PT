#include "AddRead.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"




//constructor: set the ApplicationManager pointer inside this action
AddRead::AddRead(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddRead::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	//Read the (Position) parameter
	pOut->PrintMessage("Read Statement: Click to Read a Variabel");

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

	pOut->PrintMessage("Please Enter var");
	var = pIn->GetVariabel(pOut);

}

void AddRead::Execute()
{
	ReadActionParameters();

	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;   
	Corner.y = Position.y;

	Read* pRead = new Read(Corner, var);

	pManager->AddStatement(pRead); // Adds the created statement to application manger's statement list
}

