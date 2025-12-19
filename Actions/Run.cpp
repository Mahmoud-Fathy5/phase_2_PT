#include "Run.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "../Statements/End.h"
#include "Validate.h"
Run::Run(ApplicationManager* pAppManager):Action(pAppManager)
{
}


void Run::ReadActionParameters()
{
	Validate valid(pManager);
	valid.Execute();
}


void Run::Execute()
{
	ReadActionParameters();
	if (!pManager->GetIsValid())
		return;
	Statement* pStat = pManager->GetStart();
	Output* pOut = pManager->GetOutput();
	while (dynamic_cast<End*>(pStat) == NULL)
	{
		pStat = pStat->Simulate(pManager);
	}
	pOut->OutputMessages("==========================");
	pOut->PrintMessage("Simulation Ended");
	pManager->killVars();
	pManager->SetIsValid(false);
}