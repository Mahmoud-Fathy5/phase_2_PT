#pragma once
#include "Action.h"
#include <fstream>
class Save : public Action
{
	ofstream OutFile;
public:
	Save(ApplicationManager* pAppManager);

	
	virtual void ReadActionParameters();

	
	virtual void Execute();

};