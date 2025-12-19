#include "AddStart.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddStart::AddStart(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddStart::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();


	pIn->GetPointClicked(Position);
	while (!(Position.x <UI.DrawingAreaWidth && Position.y >UI.ToolBarHeight && Position.y < (UI.height - UI.StatusBarHeight))) {
		(pManager->GetOutput())->PrintMessage("You Should Draw in the Drawing Area Only, Click anywhere in the Drawing Area");
		pIn->GetPointClicked(Position);
	}
	while ((pManager->GetStatement(Position))) {
		(pManager->GetOutput())->PrintMessage("You cannot Put Statement Above The other , click anywhere else");
		pIn->GetPointClicked(Position);
	}
}

void AddStart::Execute()
{
	if (Start::exsit) {
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("You cannot add more than one Start");
		return;
	}
	ReadActionParameters();
	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.OVAL_WDTH/ 2;
	Corner.y = Position.y;

	Start* pStart = new Start(Corner);
	

	pManager->AddStatement(pStart); // Adds the created statement to application manger's statement list
}

