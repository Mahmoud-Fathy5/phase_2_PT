#pragma once
#include "Action.h"
#include <fstream>
class GenerateCode : public Action
{
private:
	ofstream CodeFile;
public:
	GenerateCode(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};