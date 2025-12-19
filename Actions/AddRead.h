#pragma once
#include "Action.h"
#include "..\Statements\Read.h"


class AddRead : public Action
{
private:
	string var;
	Point Position;	
public:
	AddRead(ApplicationManager* pAppManager);
	virtual void ReadActionParameters();
	virtual void Execute();

};
