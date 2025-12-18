#include "Debug.h"
#include "../Statements/End.h"
Debug::Debug(ApplicationManager* pAppManager):Action(pAppManager)
{
}

void Debug::ReadActionParameters()
{
	
}

void Debug::Execute()
{
	Statement* pStat = pManager->GetStart();
	if(pManager->GetSelectedStatement() != NULL)
		pManager->GetSelectedStatement()->SetSelected(false);
	pStat->SetSelected(true);
	pManager->SetSelectedStatement(pStat);
	pManager->UpdateInterface();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	while (dynamic_cast<End*>(pStat) == NULL)
	{
		Point P;
		pIn->GetPointClicked(P);
		pStat->SetSelected(false);
		pManager->printVars();
		pOut->OutputMessages("==========================");
		pStat = pStat->Simulate(pManager);
		pStat->SetSelected(true);
		pManager->SetSelectedStatement(pStat);
		pManager->UpdateInterface();
	}
	Point P;
	pIn->GetPointClicked(P);
	pOut->OutputMessages("==========================");
	pOut->PrintMessage("Simulation Ended");

	pStat->SetSelected(false);
	pManager->SetSelectedStatement(NULL);
	pManager->killVars();

}