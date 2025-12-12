#ifndef ADD_START_H
#define ADD_START_H
#include "Action.h"
#include "..\Statements\Start.h"


class AddStart : public Action
{
private:

	Point Position;	//Position where the user clicks to add the stat.


public:
	AddStart(ApplicationManager* pAppManager);

	//Read Assignemt statements position
	virtual void ReadActionParameters();

	//Create and add an assignemnt statement to the list of statements
	virtual void Execute();

};







#endif
