#pragma once
#include "Action.h"
#include <fstream>
class Save : public Action
{
	ofstream OutFile;
public:
	Save(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};