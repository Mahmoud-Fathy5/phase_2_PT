#include "Edit.h"





#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Edit::Edit(ApplicationManager* pAppManager) :Action(pAppManager)
{
	//pSelected = NULL;
}

void Edit::ReadActionParameters()
{
	pStat = pManager->GetSelectedStatement();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();






}

void Edit::Execute()
{
	ReadActionParameters();
	
	if (pStat == NULL)
	{
		(pManager->GetOutput())->PrintMessage("No Statement Selected to edit");
		return;
	}
	else
	{
		pStat->Edit(pManager);
	}
	

}