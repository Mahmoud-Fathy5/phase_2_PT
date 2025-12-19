#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"


class Paste : public Action
{
private:

	Statement* pStat_copy;
	Point Position;

public:

	Paste(ApplicationManager* pAppManager);

	
	virtual void ReadActionParameters();

	
	virtual void Execute();

};
