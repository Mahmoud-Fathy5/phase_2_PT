#include "Copy.h"


Copy::Copy(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Copy::ReadActionParameters()
{
	pStat = pManager->GetSelectedStatement();
}

void Copy::Execute()
{
	ReadActionParameters();

	if (pStat != NULL) {
		pManager->SetClipboard(pStat);
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("Copy Is Done ");
		pManager->set_Copy0_Cut1(0);
	}
	else {
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("There Is No Selected Statment ");
	}

}
