#include "AddEnd.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
AddEnd::AddEnd(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void AddEnd::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	
	(pManager->GetOutput())->PrintMessage("Click to add End Statement");
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
}

void AddEnd::Execute()
{
	if (End::exist) {
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("You cannot add more than one End");
		return;
	}
	ReadActionParameters();

	Point Corner;
	Corner.x = Position.x - UI.OVAL_WDTH / 2;
	Corner.y = Position.y;

	End* pEnd = new End(Corner);


	pManager->AddStatement(pEnd); // Adds the created statement to application manger's statement list
}

