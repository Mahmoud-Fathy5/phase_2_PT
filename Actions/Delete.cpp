#include "Delete.h"


Delete::Delete(ApplicationManager* pAppManager):Action(pAppManager)
{
}

void Delete::ReadActionParameters()
{
	pStat = pManager->GetSelectedStatement();
	pCon = pManager->GetSelectedConn();
}

void Delete::Execute()
{
	ReadActionParameters();

	if (pStat !=NULL){
		//delete statmen with its connectors
		pManager->DeleteStat(pStat);
		pManager->SetSelectedStatement(NULL);
	}
	else if (pCon != NULL) {
		//delete connectors
		pManager->DeleteConn(pCon);
		pManager->SetSelectedConn(NULL);
	}
	else {
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("There Is No Selected Statment or Connector");
	}

}
