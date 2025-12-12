#pragma once

#include "Action.h"
#include "..\Statements\ValueAssign.h"
#include "..\Connector.h"


class Edit : public Action
{
private:

	Point Position;	//Position where the user clicks to add the stat.

	Statement* pStat;
	//Statement* pSelected;

	Action* pAc;



public:

	Edit(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};







