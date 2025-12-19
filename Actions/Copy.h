#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"


class Copy : public Action
{
private:

	Statement* pStat;

public:

	Copy(ApplicationManager* pAppManager);

	
	virtual void ReadActionParameters();

	
	virtual void Execute();

};
