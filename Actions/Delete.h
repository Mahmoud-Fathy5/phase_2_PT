#pragma once
#include "../Connector.h"
#include "Action.h"
#include "..\ApplicationManager.h"


class Delete : public Action
{
private:

	Statement* pStat;
	Connector* pCon;

public:

	Delete(ApplicationManager* pAppManager);

	virtual void ReadActionParameters();

	virtual void Execute();

};







