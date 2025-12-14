#include "ApplicationManager.h"
#include "Actions\AddValueAssign.h"
#include "./Actions\AddStart.h"
#include "./Actions\AddEnd.h"
#include "./Actions\AddAssignOperator.h"
#include "./Actions\AddAssignVariable.h"
#include "./Actions\AddDeclare.h"
#include "./Actions\AddRead.h"
#include "./Actions\AddWrite.h"
#include "./Actions\AddIf.h"
#include "./Actions\Select.h"
#include"./Actions\Delete.h"
#include"./Actions\Copy.h"
#include"./Actions\Paste.h"
#include"./Actions\Edit.h"
#include"./Actions\Cut.h"
#include"./Actions\Validate.h"


#include "GUI\Input.h"
#include "GUI\Output.h"
#include "./Actions/AddConn.h"
#include "Actions/Save.h"
#include "Actions/Run.h"
#include "Actions/Debug.h"
#include "Actions/GenerateCode.h"
//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	StatCount = 0;
	ConnCount = 0;
	VarCount = 0;
	pSelectedStat = NULL;	//no Statement is selected yet
	pClipboard = NULL;
	pSelectedConn = NULL;
	 
	//Create an array of Statement pointers and set them to NULL		
	for(int i=0; i<MaxCount; i++)
	{
		StatList[i] = NULL;	
		ConnList[i] = NULL;
	}
}


//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//


ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to ActioType, create the corresponding action object
	switch (ActType)
	{
		case ADD_VALUE_ASSIGN:
			pAct = new AddValueAssign(this);
			break;

		case ADD_CONDITION:
			pAct = new AddIf(this);
			break;

		case SELECT:
			///create Select Action here
			pAct = new Select(this);
			pOut->PrintMessage("LOL");
			break;

		case DEL:
			pAct= new Delete(this);
			break;

		case COPY:
			pAct = new Copy(this);
			break;
		case CUT:
			pAct = new Cut(this);
			break;
		case PASTE:
			pAct = new Paste(this);
			break;
		case EDIT_STAT:
			pAct = new Edit(this);
			break;
		case SAVE:
			pAct = new Save(this);
			break;
		case LOAD:
			pAct = new Load(this);
			break;

		case EXIT:
			///create Exit Action here
			
			break;
		
		case STATUS:
			return;

		case ADD_START:
			pAct = new AddStart(this);
			break;
		case ADD_END:
			pAct = new AddEnd(this);
			break;
		case ADD_OPER_ASSIGN:
			pAct = new AddAssignOperator(this);
			break;
		case ADD_VAR_ASSIGN:
			pAct = new AddAssignVariable(this);
			break;
		case ADD_DECLARE_VARIABLE:
			pAct = new AddDeclare(this);
			break;
		case ADD_READ:
			pAct = new AddRead(this);
			break;
		case ADD_WRITE:
			pAct = new AddWrite(this);
			break;
		case ADD_CONNECTOR:
			pAct = new AddConn(this);
			break;
		case SWITCH_SIM_MODE:
			pOut->CreateSimulationToolBar();
			break;
		case SWITCH_DSN_MODE:
			pOut->CreateDesignToolBar();
			break;
		
		case VALIDATE:
			pAct = new Validate(this);
			break;

		case RUN:
			pAct = new Run(this);
			break;
		case DEBUG:
			pAct = new Debug(this);
			break;
		case GENERATE_CODE:
			pAct = new GenerateCode(this);
			break;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//Action is not needed any more ==> delete it
	}
}



//==================================================================================//
//						Statements Management Functions								//
//==================================================================================//


//Add a statement to the list of statements
void ApplicationManager::AddStatement(Statement *pStat)
{
	if(StatCount < MaxCount)
		StatList[StatCount++] = pStat;
	
}

////////////////////////////////////////////////////////////////////////////////////
Statement *ApplicationManager::GetStatement(Point P) const
{
	//If this point P(x,y) belongs to a statement return a pointer to it.
	//otherwise, return NULL
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->isInside(P))
		{
			return StatList[i];
		}
	}
	return NULL;
	
	//	if (dynamic_cast<ValueAssign*>(StatList[i]))
	//	{
	//		ValueAssign* pStat = static_cast<ValueAssign*>(StatList[i]);
	//		if (P.x <= pStat->GetLeftCorner().x + UI.ASSGN_WDTH
	//			&& P.x >= pStat->GetLeftCorner().x - UI.ASSGN_WDTH
	//			&& P.y >= pStat->GetLeftCorner().y
	//			&& P.y <= pStat->GetLeftCorner().y + UI.ASSGN_HI)
	//		{

	//			return pStat;
	//		}
	//		
	//	}
	//	else if (dynamic_cast<VariableAssign*>(StatList[i]))
	//	{

	//		VariableAssign* pStat = static_cast<VariableAssign*>(StatList[i]);
	//		if (P.x <= pStat->GetLeftCorner().x + UI.ASSGN_WDTH
	//			&& P.x >= pStat->GetLeftCorner().x - UI.ASSGN_WDTH
	//			&& P.y >= pStat->GetLeftCorner().y
	//			&& P.y <= pStat->GetLeftCorner().y + UI.ASSGN_HI)
	//		{
	//			return pStat;
	//		}
	//		
	//	}

	//	else if (dynamic_cast<AssignOperator*>(StatList[i]))
	//	{
	//		AssignOperator* pStat = static_cast<AssignOperator*>(StatList[i]);
	//		if (P.x <= pStat->GetLeftCorner().x + UI.ASSGN_WDTH
	//			&& P.x >= pStat->GetLeftCorner().x - UI.ASSGN_WDTH
	//			&& P.y >= pStat->GetLeftCorner().y
	//			&& P.y <= pStat->GetLeftCorner().y + UI.ASSGN_HI)
	//		{


	//			return pStat;
	//		}
	//		
	//	}
	//	else if (dynamic_cast<End*>(StatList[i]))
	//	{
	//		End* pStat = static_cast<End*>(StatList[i]);
	//		if (P.x >= pStat->GetLeftCorner().x
	//			&& P.x <= pStat->GetLeftCorner().x + UI.OVAL_WDTH
	//			&& P.y >= pStat->GetLeftCorner().y
	//			&& P.y <= pStat->GetLeftCorner().y + UI.OVAL_HI)
	//		{

	//			return pStat;
	//		}

	//	}

	//	else if (dynamic_cast<Start*>(StatList[i]))
	//	{
	//		Start* pStat = static_cast<Start*>(StatList[i]);
	//		if (
	//			P.x >= pStat->GetLeftCorner().x
	//			&& P.x <= pStat->GetLeftCorner().x + UI.OVAL_WDTH
	//			&& P.y >= pStat->GetLeftCorner().y
	//			&& P.y <= pStat->GetLeftCorner().y + UI.OVAL_HI)
	//		{


	//			return pStat;
	//		}
	//		
	//	}


	//	else if (dynamic_cast<Read*>(StatList[i]))
	//	{
	//		Read* pStat = static_cast<Read*>(StatList[i]);
	//		if (P.x >= pStat->GetLeftCorner().x
	//			&& P.x <= pStat->GetLeftCorner().x + UI.ASSGN_WDTH
	//			&& P.y >= pStat->GetLeftCorner().y
	//			&& P.y <= pStat->GetLeftCorner().y + UI.ASSGN_HI)
	//		{

	//			return pStat;
	//		}
	//		
	//	}

	//	else if (dynamic_cast<Declare*>(StatList[i]))
	//	{
	//		Declare* pStat = static_cast<Declare*>(StatList[i]);
	//		if (P.x < pStat->GetLeftCorner().x + UI.ASSGN_WDTH
	//			&& P.x > pStat->GetLeftCorner().x
	//			&& P.y > pStat->GetLeftCorner().y
	//			&& P.y < pStat->GetLeftCorner().y + UI.ASSGN_HI)
	//		{


	//			return pStat;
	//		}
	//		
	//	}
	//	else if (dynamic_cast<If*>(StatList[i]))
	//	{
	//		If* pStat = static_cast<If*>(StatList[i]);

	//		/*double slope1 = ((pStat->GetLeftCorner().y - (pStat->GetLeftCorner().y + UI.COND_HI/2))
	//			/ ((pStat->GetLeftCorner().x + UI.COND_WDTH / 2) - pStat->GetLeftCorner().x));



	//		double slope2 = ((pStat->GetLeftCorner().y - (pStat->GetLeftCorner().y + UI.COND_HI / 2))
	//			/ ((pStat->GetLeftCorner().x + UI.COND_WDTH / 2) - (pStat->GetLeftCorner().x+ UI.COND_WDTH)));



	//		double slope3 = (((pStat->GetLeftCorner().y+UI.COND_HI/2) - (pStat->GetLeftCorner().y + UI.COND_HI ))
	//			/ ((pStat->GetLeftCorner().x + UI.COND_WDTH)  - (pStat->GetLeftCorner().x + UI.COND_WDTH/2)));



	//		double slope4= (((pStat->GetLeftCorner().y + UI.COND_HI / 2) - (pStat->GetLeftCorner().y + UI.COND_HI))
	//			/ (pStat->GetLeftCorner().x  - (pStat->GetLeftCorner().x + UI.COND_WDTH / 2)));


	//		

	//		
	//		if ((P.y- pStat->GetLeftCorner().y)/(P.x- pStat->GetLeftCorner().x + UI.COND_WDTH / 2)>=slope1&&
	//			(P.y - pStat->GetLeftCorner().y) / (P.x - pStat->GetLeftCorner().x + UI.COND_WDTH ) >= slope2&&
	//			(P.y - pStat->GetLeftCorner().y + UI.COND_HI / 2) / (P.x - pStat->GetLeftCorner().x + UI.COND_WDTH / 2) <= slope3&&
	//			(P.y - pStat->GetLeftCorner().y + UI.COND_HI ) / (P.x - pStat->GetLeftCorner().x) <= slope4)*/
	//		if (P.x >= pStat->GetLeftCorner().x
	//			&& P.x <= pStat->GetLeftCorner().x + UI.COND_WDTH
	//			&& P.y >= pStat->GetLeftCorner().y
	//			&& P.y <= pStat->GetLeftCorner().y + UI.COND_HI)
	//		{
	//			return pStat;
	//		}

	//	}
	//		else if (dynamic_cast<Write*>(StatList[i]))
	//		{
	//			Write* pStat = static_cast<Write*>(StatList[i]);
	//			if (P.x >= pStat->GetLeftCorner().x
	//				&& P.x <= pStat->GetLeftCorner().x + UI.ASSGN_WDTH
	//				&& P.y >= pStat->GetLeftCorner().y
	//				&& P.y <= pStat->GetLeftCorner().y + UI.ASSGN_HI)
	//			{

	//				return pStat;
	//			}

	//		

	//	
	//	
	//}
	//Statement* pStat = NULL;
	//return pStat;

	///Add your code here to search for a statement given a point P(x,y)	
	///WITHOUT breaking class responsibilities
	
}
void ApplicationManager::AddConnector(Connector* pConn)
{
	if (ConnCount < MaxCount)
		ConnList[ConnCount++] = pConn;

}
Connector* ApplicationManager::GetConnector(Point P) const
{
	for (int i = 0; i < ConnCount; i++)
	{
		Point p1 = ConnList[i]->getStartPoint();
		Point p2 = ConnList[i]->getEndPoint();
		if (p1.y < p2.y)
		{
			if (p1.x == p2.x)
			{
				if (P.x >= p1.x - 8 && P.x <= p1.x + 8 && P.y <= p2.y && P.y >= p1.y)
				{
					Connector* pCon = ConnList[i];
					return pCon;
				}

			}
			else if (p2.x > p1.x)
			{
				if (P.y >= p1.y - 8 && P.y <= p1.y + 8 && P.x <= p2.x && P.x >= p1.x
					|| P.x >= p2.x - 8 && P.x <= p2.x + 8 && P.y >= p1.y && P.y <= p2.y)
				{
					Connector* pCon = ConnList[i];
					return pCon;
				}
			}
			else
			{
				if (P.y >= p1.y - 8 && P.y <= p1.y + 8 && P.x <= p1.x && P.x >= p2.x
					|| P.x >= p2.x - 8 && P.x <= p2.x + 8 && P.y >= p1.y && P.y <= p2.y)
				{
					Connector* pCon = ConnList[i];
					return pCon;
				}
			}
		}
		else if (p1.y == p2.y && p2.x > p1.x)
		{
			if (P.y >= p1.y - 8 && P.y <= p1.y && P.x <= p2.x && P.x >= p1.x)
			{
				Connector* pCon = ConnList[i];
				return pCon;
			}
		}
		else if (p1.y == p2.y && p2.x < p1.x)
		{
			if (P.y >= p1.y - 8 && P.y <= p1.y && P.x <= p1.x && P.x >= p2.x)
			{
				Connector* pCon = ConnList[i];
				return pCon;
			}
		}
		else if (p1.y > p2.y)
		{
			if (p1.x > p2.x)
			{
				if (P.y >= p1.y - 8 && P.y <= p1.y + 8 && P.x >= p1.x && P.x <= p1.x+100
					|| P.x <= p1.x+100 + 8 && P.x >= p1.x+100 - 8 && P.y <= p1.y && P.y >= p2.y
					|| P.y <= p2.y + 8 && P.y >= p2.y - 8 && P.x <= p1.x+100 && P.x >= p2.x)
				{
					Connector* pCon = ConnList[i];
					return pCon;
				}
			}
			else
			{
				if (P.y >= p1.y - 8 && P.y <= p1.y + 8 && P.x >= p1.x - 100 && P.x <= p1.x
					|| P.x <= p1.x + 8 - 100 && P.x >= p1.x - 8 - 100 && P.y <= p1.y && P.y >= p2.y
					|| P.y <= p2.y + 8 && P.y >= p2.y - 8 && P.x >= p1.x - 100 && P.x <= p2.x)
				{
					Connector* pCon = ConnList[i];
					return pCon;
				}
			}
		}
		
	}
	Connector* pCon = NULL;
	return pCon;
}

//Returns the selected connector
Connector* ApplicationManager::GetSelectedConn()const
{
	return pSelectedConn;
}

//sets the selected connector
void ApplicationManager::SetSelectedConn(Connector* pConn)
{
	pSelectedConn = pConn;
}

void ApplicationManager::DeleteConn(Connector* pConn)
{
	if (pConn != NULL) {
		int index;
		for (int i = 0; i < ConnCount; i++) {
			if (pConn == ConnList[i]) {
				index = i;
				break;
			}
		}

		for (int i = index; i < ConnCount - 1; i++) {
			ConnList[i] = ConnList[i + 1];
		}
		ConnList[ConnCount - 1] = NULL;
		ConnCount--;
		(pConn->getSrcStat())->SetOutConn1(NULL);
		delete pConn;
	}
	
}

void ApplicationManager::DeleteStat(Statement* pStat)
{

	if (pStat != NULL) {
		DeleteConn(pStat->GetOutConn1());
		if (dynamic_cast<If*>(pStat)) {
			DeleteConn(pStat->GetOutConn2());
		}

		for (int i = 0; i < ConnCount;i++) {
			if ((ConnList[i]->getDstStat()) == pStat ) {
				DeleteConn(ConnList[i]);
			}
		}

		int index;
		for (int i = 0; i < StatCount; i++) {
			if (pStat == StatList[i]) {
				index = i;
				break;
			}
		}
		for (int i = index; i < StatCount - 1; i++) {
			StatList[i] = StatList[i + 1];
		}
		StatList[StatCount - 1] = NULL;
		StatCount--;
		delete pStat;
	}
}
	
	


void ApplicationManager::saveStatements(ofstream& OutFile)
{
	OutFile << StatCount << "\n";
	for (int i = 0; i < StatCount; i++)
		StatList[i]->Save(OutFile);
}

void ApplicationManager::saveConn(ofstream& OutFile)
{
	OutFile << ConnCount << "\n";
	for (int i = 0; i < ConnCount; i++)
		ConnList[i]->Save(OutFile);
}

Statement* ApplicationManager::FindStatement(int id)
{
	for (int i = 0; i < StatCount; i++)
	{
		if (StatList[i]->GetID() == id)
			return StatList[i];
	}
	return nullptr;
}










////////////////////////////////////////////////////////////////////////////////////
//Returns the selected statement
Statement *ApplicationManager::GetSelectedStatement() const
{	return pSelectedStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the statement selected by the user
void ApplicationManager::SetSelectedStatement(Statement *pStat)
{	pSelectedStat = pStat;	}

////////////////////////////////////////////////////////////////////////////////////
//Returns the Clipboard
Statement *ApplicationManager::GetClipboard() const
{	return pClipboard;	}

////////////////////////////////////////////////////////////////////////////////////
//Set the Clipboard
void ApplicationManager::SetClipboard(Statement *pStat)
{	pClipboard = pStat;	}

bool ApplicationManager::get_Copy0_Cut1() const
{
	return	this->Copy0_or_Cut1;
}
void ApplicationManager::set_Copy0_Cut1(bool b)
{
	this->Copy0_or_Cut1 = b;
}


//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//


//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();

	//Draw all statements
	for(int i=0; i<StatCount; i++)
		StatList[i]->Draw(pOut);
	
	//Draw all connections
	for(int i=0; i<ConnCount; i++)
		ConnList[i]->Draw(pOut);

}

Statement* ApplicationManager::GetStart()
{
	for (int i = 0; i < StatCount; i++)
	{
		if (dynamic_cast<Start*>(StatList[i]))
			return StatList[i];
	}
	return NULL;
}
void ApplicationManager::AddVar(variable* v)
{
	if (VarCount < MaxCount)
		Vars[VarCount++] = v;

}
variable* ApplicationManager::FindVar(string name)
{
	for (int i = 0; i < VarCount; i++)
	{
		if (Vars[i]->name == name)
			return Vars[i];
	}
	return NULL;
}
void ApplicationManager::printVars() const
{
	for (int i = 0; i < VarCount; i++)
	{
		pOut->OutputMessages(Vars[i]->name + " = " + to_string(Vars[i]->value));
	}
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////


//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<StatCount; i++)
		delete StatList[i];
	for(int i=0; i<ConnCount; i++) //ConnCount
		delete ConnList[i];
	for (int i = 0; i < VarCount; i++)
		delete Vars[i];

	delete pIn;
	delete pOut;
	
}

Statement*ApplicationManager:: GetStart()
{
	Start* pStart;
	for (int i = 0; i < StatCount; i++)
	{
		if (dynamic_cast<Start*>(StatList[i]))
		{
			pStart = (Start*)StatList[i];
			return pStart;
		}
	}
	return NULL;
}
