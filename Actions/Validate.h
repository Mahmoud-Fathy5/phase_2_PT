#pragma once

#include "Action.h"
#include "..\Statements\Start.h"
#include "..\Connector.h"



//Base class for all possible actions
class Validate: public Action
{
private:

	//Pointer to ApplicationManager because action needs this pointer for its functions
	

	Point Position;
	
	//int x=0;
	//int y=0;
	Point p;

	Statement* pStat;
	
	Statement* pStat1;

	Statement* pStat2;

	Connector* pCon;

public:

	Validate(ApplicationManager* pAppManager);
	

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute() ;

	void FirstBranchConditionCheck();

	void SecondBranchConditionCheck();

	bool NormalStatementCheck(Statement*);
	
};

