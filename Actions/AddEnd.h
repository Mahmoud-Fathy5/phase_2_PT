#ifndef ADD_END_H
#define ADD_END_H
#include "Action.h"
#include "..\Statements\End.h"


class AddEnd : public Action
{
private:

	Point Position;	//Position where the user clicks to add the stat.


public:
	AddEnd(ApplicationManager* pAppManager);

	
	virtual void ReadActionParameters();

	//Create and add an End statement to the list of statements
	virtual void Execute();

};







#endif