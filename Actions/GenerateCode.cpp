#include "GenerateCode.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include "../Statements/End.h"
#include "../Statements/If.h"
GenerateCode::GenerateCode(ApplicationManager* pAppManager):Action(pAppManager)
{
}

void GenerateCode::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Enter File Name");
	string FileName = pIn->GetString(pOut);
	system("mkdir Codes");
	CodeFile.open("Codes//" + FileName + ".cpp");
}

void GenerateCode::Execute()
{
	ReadActionParameters();
	bool if_Exist = false;
	If* pIfStat = NULL;
	Statement* pStat = pManager->GetStart();
	Output* pOut = pManager->GetOutput();
	if (pStat == NULL)
	{
		pOut->PrintMessage("There is no Start Statement");
		return;
	}
	CodeFile << "#include <iostream>" << "\n";
	CodeFile << "using namespace std;" << "\n";
	CodeFile << "int main(){" << "\n";
	while (dynamic_cast<End*>(pStat) == NULL)
	{
		if (dynamic_cast<If*>(pStat))
		{
			if_Exist = true;
			pIfStat = (If*)pStat;
		}
		CodeFile << "\t";
		pStat = pStat->GenerateCode(CodeFile);
	}
	pStat->GenerateCode(CodeFile);
	if (if_Exist && pIfStat->GetVisted())
	{
		pStat = (Statement*)pIfStat;
		while (pStat != NULL)
		{
			CodeFile << "\t";
			pStat = pStat->GenerateCode(CodeFile);
		}
	}
	CodeFile << "}\n";
	pOut->PrintMessage("Code Generated");
	CodeFile.close();
}