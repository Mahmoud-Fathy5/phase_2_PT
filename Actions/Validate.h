#pragma once

#include "Action.h"
#include "..\Statements\Start.h"
#include "..\Connector.h"



//Base class for all possible actions
class Validate: public Action
{
private:
	bool skip;
public:

	Validate(ApplicationManager* pAppManager);
	

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	void Execute_if(Statement* ptr);
	
};

