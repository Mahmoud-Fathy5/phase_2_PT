#pragma once
#include "../Connector.h"
#include "Action.h"
#include "..\ApplicationManager.h"


class Delete : public Action
{
private:

	Statement* pStat;
	//Statement* pSelected;
	Connector* pCon;

public:

	Delete(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};







