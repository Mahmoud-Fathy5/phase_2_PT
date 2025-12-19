#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"


class Cut : public Action
{
private:

	Statement* pStat;

public:

	Cut(ApplicationManager* pAppManager);

	
	virtual void ReadActionParameters();

	
	virtual void Execute();

};
