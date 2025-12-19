#pragma once


#include "Action.h"
#include "..\Statements\If.h"

class AddIf : public Action
{
private:
	string LHS;
	string op;
	string RHS;
	

	Point Position;	

public:
	AddIf(ApplicationManager* pAppManager);

	
	virtual void ReadActionParameters();

	virtual void Execute();

};

