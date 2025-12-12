#include "AddRead.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

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
	pOut->ClearStatusBar();

	//TODO: Ask the user in the status bapr to enter the LHS and set the data member
	pOut->PrintMessage("Please Enter var");
	var = pIn->GetVariabel(pOut);

	//TODO: Ask the user in the status bar to enter the RHS and set the data member

	//Note: You should validate the LHS to be variable name and RHS to be a value
	//      Call the appropriate functions for this.
}

void AddRead::Execute()
{
	ReadActionParameters();


	//Calculating left corner of assignement statement block
	Point Corner;
	Corner.x = Position.x - UI.ASSGN_WDTH / 2;   // need to be considerdddd
	Corner.y = Position.y;

	Read* pRead = new Read(Corner, var);
	//TODO: should set the LHS and RHS of pAssign statement
	//      with the data members set and validated before in ReadActionParameters()

	pManager->AddStatement(pRead); // Adds the created statement to application manger's statement list
}

