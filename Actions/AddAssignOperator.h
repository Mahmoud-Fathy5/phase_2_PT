#ifndef ADD_ASSIGN_OPERATOR_H
#define ADD_ASSIGN_OPERATOR_H

#include "Action.h"
#include "..\Statements\AssignOperator.h"

class AddAssignOperator : public Action
{
private:
	string LHS;
	string op;
	string RHS_1;
	string RHS_2;
	
	

	Point Position;	//Position where the user clicks to add the stat.
	

public:
	AddAssignOperator(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};

#endif