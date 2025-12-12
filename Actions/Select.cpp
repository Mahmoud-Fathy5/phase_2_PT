#include "Select.h"



#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Select::Select(ApplicationManager* pAppManager) :Action(pAppManager)
{
	//pSelected = NULL;
}

void Select::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();


	pIn->GetPointClicked(Position);
	pOut->ClearStatusBar();

	



	
}

void Select::Execute()
{
	ReadActionParameters();


	
	
	pStat = pManager->GetStatement(Position);
	pCon = pManager->GetConnector(Position);
	
	if (pCon == NULL&&pStat==NULL)
	{
		return;
	}

	if (pStat != NULL && pCon == NULL)
	{
		if (pManager->GetSelectedConn() != NULL)
		{
			(pManager->GetSelectedConn())->SetSelected(false);
			pManager->SetSelectedConn(NULL);
		}

		if (pManager->GetSelectedStatement() != NULL &&pManager->GetSelectedStatement()!=pStat)
		{
			(pManager->GetSelectedStatement())->SetSelected(false);
			pStat->SetSelected(true);
			pManager->SetSelectedStatement(pStat);
			return;
		}

		if (pManager->GetSelectedStatement() != NULL && pManager->GetSelectedStatement() == pStat)
		{
			(pManager->GetSelectedStatement())->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
			return;
			
		}
		if (pManager->GetSelectedStatement() == NULL)
		{
			pStat->SetSelected(true);
			pManager->SetSelectedStatement(pStat);
		}
		return;

	}
	else if(pStat==NULL&&pCon!=NULL)
	{

		if (pManager->GetSelectedStatement() != NULL)
		{
			(pManager->GetSelectedStatement())->SetSelected(false);
			pManager->SetSelectedStatement(NULL);
		}

		if (pManager->GetSelectedConn() != NULL && pManager->GetSelectedConn() != pCon)
		{
			(pManager->GetSelectedConn())->SetSelected(false);
			pCon->SetSelected(true);
			pManager->SetSelectedConn(pCon);
			return;
		}

		if (pManager->GetSelectedConn() != NULL && pManager->GetSelectedConn() == pCon)
		{
			(pManager->GetSelectedConn())->SetSelected(false);
			pManager->SetSelectedConn(NULL);
			return;

		}
		if (pManager->GetSelectedConn() == NULL)
		{
			pCon->SetSelected(true);
			pManager->SetSelectedConn(pCon);
		}
		return;
	}

	
	


	
}

