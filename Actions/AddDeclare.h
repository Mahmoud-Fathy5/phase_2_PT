#pragma once

#include "Action.h"
#include "..\Statements\Declare.h"

class AddDeclare : public Action
{
private:
	string var;
	// in the data members of the actions
	// we put the paramaters of the action
	// to be set in ReadActionParameters() then used in Execute()

	Point Position;	//Position where the user clicks to add the stat.

public:
	AddDeclare(ApplicationManager *pAppManager);

	virtual void ReadActionParameters();
	

	virtual void Execute() ;
	
};
