#pragma once
#include "Action.h"
#include <fstream>

class Load : public Action
{
	ifstream InFile;
public:
	Load(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};