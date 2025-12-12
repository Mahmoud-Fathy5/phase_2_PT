#include "AddConn.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include"..\Statements/Start.h"
#include"..\Statements/End.h"

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

	Connector* pConnector = new Connector(SrcStat, DstStat);
	pConnector->setStartPoint(SrcStat->GetOutLet());
	if (dynamic_cast<End*>(SrcStat))
	{
		(pManager->GetOutput())->PrintMessage("Cannot Set End as a Start Point");
		return;
	}
	pConnector->setEndPoint(DstStat->GetInLet());
	if (dynamic_cast<Start*>(DstStat))
	{
		(pManager->GetOutput())->PrintMessage("Cannot Set Start as an End Point");
		return;
	}
	pManager->AddConnector(pConnector);

}