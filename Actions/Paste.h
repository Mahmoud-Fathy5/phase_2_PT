#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"


class Paste : public Action
{
private:

	Statement* pStat_copy;
	Point Position;

public:

	Paste(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};
