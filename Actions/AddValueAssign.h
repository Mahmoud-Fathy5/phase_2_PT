#ifndef ADD_VALUE_ASSIGN_H
#define ADD_VALUE_ASSIGN_H

#include "Action.h"
#include "..\Statements\ValueAssign.h"


class AddValueAssign : public Action
{
private:
	string LHS;
	double RHS;
	

	Point Position;

public:
	AddValueAssign(ApplicationManager *pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();
	
	//Create and add an assignemnt statement to the list of statements
	virtual void Execute() ;
	
};

#endif