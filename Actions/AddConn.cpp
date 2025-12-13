#include "AddConn.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include"..\Statements/Start.h"
#include"..\Statements/End.h"

#include"..\Statements/If.h"

#include <sstream>
using namespace std;


AddConn::AddConn(ApplicationManager* pAppManager):Action(pAppManager)
{
}

void AddConn::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Add Connector: Click on the source Statement");
	//Point p;
	pIn->GetPointClicked(start);
	while (pManager->GetStatement(start) == NULL)
	{
		pOut->PrintMessage("Invalid");
		pIn->GetPointClicked(start);
	}
	SrcStat = pManager->GetStatement(start);
	pOut->PrintMessage("Click on the distnation Statement");
	pIn->GetPointClicked(end);
	pOut->PrintMessage("Clicked");
	while (pManager->GetStatement(end) == NULL)
	{
		pOut->PrintMessage("Invalid");
		pIn->GetPointClicked(end);
	}
	DstStat = pManager->GetStatement(end);
}

void AddConn::Execute()
{

	ReadActionParameters();
	if (SrcStat == DstStat)
	{
		(pManager->GetOutput())->PrintMessage("Cannot Add Connector");
		return;

	}

	if (dynamic_cast<End*>(SrcStat))
	{
		(pManager->GetOutput())->PrintMessage("Cannot Add Connector");
		return;
	}



	if (dynamic_cast<Start*>(DstStat))
	{
		(pManager->GetOutput())->PrintMessage("Cannot Add Connector");
		return;
	}





	if (dynamic_cast<If*>(SrcStat) && SrcStat->GetOutConn1() != NULL && SrcStat->GetOutConn2() != NULL)
	{
		(pManager->GetOutput())->PrintMessage("Cannot Add Conector");
		return;
	}



	if (dynamic_cast<If*>(SrcStat)==NULL   &&    SrcStat->GetOutConn1() != NULL)
	{
		(pManager->GetOutput())->PrintMessage("Cannot Add Connector");
		return;
	}


	Connector* pConnector = new Connector(SrcStat, DstStat);
	if (dynamic_cast<If*>(SrcStat) && SrcStat->GetOutConn1() == NULL && SrcStat->GetOutConn2() == NULL)
	{
		
		pConnector->setStartPoint(SrcStat->GetOutLet1());
		pConnector->setEndPoint(DstStat->GetInLet());
		SrcStat->SetOutConn1(pConnector);
		pManager->AddConnector(pConnector);
		return;
	}

	if (dynamic_cast<If*>(SrcStat) && SrcStat->GetOutConn1() != NULL && SrcStat->GetOutConn2() == NULL)
	{
		
		pConnector->setStartPoint(SrcStat->GetOutLet2());
		pConnector->setEndPoint(DstStat->GetInLet());
		SrcStat->SetOutConn2(pConnector);
		pManager->AddConnector(pConnector);
		return;
	}

	if (dynamic_cast<If*>(SrcStat)==NULL)
	{
		SrcStat->SetOutConn1(pConnector);
		pConnector->setStartPoint(SrcStat->GetOutLet1());
	}
	

	

	pManager->AddConnector(pConnector);


}