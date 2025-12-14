#include "Validate.h"

#include "..\Statements\If.h"

#include "..\Statements\End.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Validate::Validate(ApplicationManager* pAppManager) :Action(pAppManager)
{
	//pValidateed = NULL;
	pStat = NULL;
	pStat1 = NULL;
	pStat2 = NULL;


	pCon = NULL;
}

void Validate::ReadActionParameters()
{
	/*Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();*/


	//pIn->GetPointClicked(Position);
	//pOut->ClearStatusBar();






}

bool Validate::NormalStatementCheck(Statement* sp)
{
	if (!sp)
		return false;

	if (dynamic_cast<End*>(sp))
		return true;

	if (!dynamic_cast<If*>(sp))
	{
		if (!sp->GetOutConn1())
			return false;

		return NormalStatementCheck(
			sp->GetOutConn1()->getDstStat()
		);
	}
	else
	{
		if (!sp->GetOutConn1() || !sp->GetOutConn2())
			return false;

		return NormalStatementCheck(sp->GetOutConn1()->getDstStat()) &&
			NormalStatementCheck(sp->GetOutConn2()->getDstStat());
	}
}













//void Validate::FirstBranchConditionCheck()
//{
//	pStat1 = (pStat->GetOutConn1())->getDstStat();
//	if (dynamic_cast<End*>(pStat))
//	{
//		return;
//	}
//	else if (dynamic_cast<If*>(pStat))
//	{
//		return FirstBranchConditionCheck();
//		return SecondBranchConditionCheck();
//	}
//	else
//	{
//		return NormalStatementCheck();
//	}
//}

//void Validate::SecondBranchConditionCheck()
//{
//	pStat = (pStat->GetOutConn2())->getDstStat();
//	if (dynamic_cast<End*>(pStat))
//	{
//		return;
//	}
//	else if (dynamic_cast<If*>(pStat))
//	{
//		/*if (pStat->GetOutConn1() == NULL || pStat->GetOutConn2() == NULL)
//		{
//
//		}*/
//		pStat = (pStat->GetOutConn1())->getDstStat();
//		return SecondBranchConditionCheck();
//	}
//	else
//	{
//		return NormalStatementCheck();
//	}
//}

//void Validate:: NormalStatementCheck(Statement*&sp)
//{
//	
//	if (dynamic_cast<End*>(sp))
//	{
//		return;
//	}
//	if (sp->GetOutConn1() == NULL)
//	{
//		(pManager->GetOutput())->PrintMessage("Error:There is no Conncetor Connected");
//		return;
//	}
//	sp=(sp->GetOutConn1())->getDstStat();
//	if (dynamic_cast<If*>(sp))
//	{
//		if (sp->GetOutConn1() == NULL || sp->GetOutConn2() == NULL)
//		{
//			(pManager->GetOutput())->PrintMessage("Error:There is no Conncetor Connected");
//			return;
//		}
//		else
//		{
//			/*sp = (pStat->GetOutConn1())->getDstStat();
//			sp = (pStat->GetOutConn2())->getDstStat();*/
//			NormalStatementCheck((sp->GetOutConn1())->getDstStat());
//			NormalStatementCheck((sp->GetOutConn2())->getDstStat());
//		}
//
//	}
//	else
//	{
//		 NormalStatementCheck(sp);
//	}
//}









void Validate::Execute()
{
	ReadActionParameters();
	pStat = pManager->GetStart();
	//firs validation
	if (pStat == NULL)
	{
		(pManager->GetOutput())->PrintMessage("Error:There is no Start Statement");
		return;
	}

	//Second Validation

	if (pStat->GetOutConn1() == NULL)
	{
		(pManager->GetOutput())->PrintMessage("Error:There is no Connector Connected");
		return;
	}
	pStat = (pStat->GetOutConn1())->getDstStat();
	if (NormalStatementCheck(pStat))
	{
		pManager->GetOutput()->PrintMessage("Validated");
	}

}












//	if (pStat->GetOutConn1() == NULL)
//	{
//		(pManager->GetOutput())->PrintMessage("Error:There is no Connector Connected");
//		return;
//	}
//	if (dynamic_cast<End*>(pStat))
//	{
//		return;
//	}
//
//
//
//
//
//	//Third Validation
//	while (true)
//	{
//
//		if (dynamic_cast<If*>(pStat))
//
//		{
//			if (pStat->GetOutConn1() == NULL || pStat->GetOutConn2() == NULL)
//			{
//				(pManager->GetOutput())->PrintMessage("Error:There is no Connector Connected");
//				return;
//			}
//			else
//			{
//				pStat = (pStat->GetOutConn1())->getDstStat();
//				//pStat2= (pStat->GetOutConn2())->getDstStat();
//			}
//		}
//		else
//		{
//			if (pStat->GetOutConn1() == NULL)
//			{
//				(pManager->GetOutput())->PrintMessage("Error:There is no Connector Connected");
//				return;
//			}
//			else
//			{
//				pStat = (pStat->GetOutConn1())->getDstStat();
//			}
//		}
//		
//	}
//	
//	
//}