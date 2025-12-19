#pragma once
#include "Action.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

class Debug :public Action
{
public:
	Debug(ApplicationManager* pAppManager);

	
	virtual void ReadActionParameters();

	
	virtual void Execute();

};