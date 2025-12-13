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
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	

	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();






}

void Edit::Execute()
{

	pStat = pManager->GetStatement(Position);

	if (pStat == NULL)
	{
		(pManager->GetOutput())->PrintMessage("No Statement Selected to edit");
		return;
	}
	else if (pStat != NULL)
	{
		if (dynamic_cast<ValueAssign*>(pStat))
		{
			
		}
	}
	ReadActionParameters();

}