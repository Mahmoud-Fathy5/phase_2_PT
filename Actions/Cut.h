#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"


class Cut : public Action
{
private:

	Statement* pStat;

public:

	Cut(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};
