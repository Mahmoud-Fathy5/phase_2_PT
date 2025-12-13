#include "Load.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "..\Statements\Statement.h"
#include "AddValueAssign.h"
#include "AddStart.h"
#include "AddEnd.h"
#include "AddAssignOperator.h"
#include "AddAssignVariable.h"
#include "AddDeclare.h"
#include "AddRead.h"
#include "Select.h"
#include "AddIf.h"
#include "AddConn.h"
#include "Save.h"

Load::Load(ApplicationManager* pAppManager):Action(pAppManager)
{
}

void Load::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	string filename;
	pOut->PrintMessage("Write file name");
	filename = pIn->GetString(pOut);
	InFile.open("SavedCharts//"+filename + ".txt");
	while (InFile.fail())
	{
		pOut->PrintMessage("Error: File not found, Enter a valid file name");
		filename = pIn->GetString(pOut);
		InFile.open(filename + ".txt");
	}
}

void Load::Execute()
{
	ReadActionParameters();
	int StatmentCount = 0;
	InFile >> StatmentCount;
	for (int i = 0; i < StatmentCount; i++)
	{
		Statement* pStatement;
		string StatType;
		InFile >> StatType;
		if (StatType == "STRT")
		{
			pStatement = new Start;
			pStatement->Load(InFile);
			pManager->AddStatement(pStatement);
		}
		else if (StatType == "END")
		{
			pStatement = new End;
			pStatement->Load(InFile);
			pManager->AddStatement(pStatement);
		}
		else if (StatType == "READ")
		{
			pStatement = new Read;
			pStatement->Load(InFile);
			pManager->AddStatement(pStatement);
		}
		else if (StatType == "OP_ASSIGN")
		{
			pStatement = new AssignOperator;
			pStatement->Load(InFile);
			pManager->AddStatement(pStatement);
		}
		else if (StatType == "VAR_ASSIGN")
		{
			pStatement = new VariableAssign;
			pStatement->Load(InFile);
			pManager->AddStatement(pStatement);
		}
		else if (StatType == "COND")
		{
			pStatement = new If;
			pStatement->Load(InFile);
			pManager->AddStatement(pStatement);
		}
		else if (StatType == "VAL_ASSIGN")
		{
			pStatement = new ValueAssign;
			pStatement->Load(InFile);
			pManager->AddStatement(pStatement);
		}
		else if (StatType == "DECLARE")
		{
			pStatement = new Declare;
			pStatement->Load(InFile);
			pManager->AddStatement(pStatement);
		}

	}
	int ConnCount = 0;
	InFile >> ConnCount;
	for (int i = 0; i < ConnCount; i++)
	{
		int srcID, dstID;
		InFile >> srcID >> dstID;
		Connector* Conn = new Connector(pManager->FindStatement(srcID), pManager->FindStatement(dstID));
		pManager->AddConnector(Conn);
	}
}