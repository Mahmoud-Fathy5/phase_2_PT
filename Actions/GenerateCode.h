#pragma once
#include "Action.h"
#include <fstream>
class GenerateCode : public Action
{
private:
	ofstream CodeFile;
public:
	GenerateCode(ApplicationManager* pAppManager);

	
	virtual void ReadActionParameters();

	
	virtual void Execute();

};