#include "Cut.h"


Cut::Cut(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Cut::ReadActionParameters()
{
	pStat = pManager->GetSelectedStatement();
}

void Cut::Execute()
{
	ReadActionParameters();

	if (pStat != NULL) {
		pManager->SetClipboard(pStat);
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("Cut Is Done ");
		pManager->set_Copy0_Cut1(1);
	}
	else {
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("There Is No Selected Statment ");
	}

}
