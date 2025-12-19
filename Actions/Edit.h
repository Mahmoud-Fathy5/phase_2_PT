#pragma once

#include "Action.h"
#include "..\Statements\ValueAssign.h"
#include "..\Connector.h"


class Edit : public Action
{
private:


	Statement* pStat;
	



public:

	Edit(ApplicationManager* pAppManager);

	
	virtual void ReadActionParameters();

	
	virtual void Execute();

};







