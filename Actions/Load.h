#pragma once
#include "Action.h"
#include <fstream>

class Load : public Action
{
	ifstream InFile;
public:
	Load(ApplicationManager* pAppManager);

	
	virtual void ReadActionParameters();

	
	virtual void Execute();

};