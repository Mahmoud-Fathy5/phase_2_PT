#pragma once
#include "Action.h"
#include "../Statements/Statement.h"
class Run : public Action
{
public:
	Run(ApplicationManager* pAppManager);

	
	virtual void ReadActionParameters();

	
	virtual void Execute();


};