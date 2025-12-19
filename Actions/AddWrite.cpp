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
	while ((pManager->GetStatement(Position))) {
		(pManager->GetOutput())->PrintMessage("You cannot Put Statement Above The other , click anywhere else");
		pIn->GetPointClicked(Position);
	}
	pOut->ClearStatusBar();

	
	pOut->PrintMessage("Please Enter Variable name or String");
	VarOrValu = pIn->GetStringlOrVariable(pOut);

}

void AddWrite::Execute()
{
	ReadActionParameters();
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;   
	Corner.y = Position.y;

	Write* pWrite = new Write(Corner, VarOrValu);

	pManager->AddStatement(pWrite); 
}

