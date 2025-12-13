#ifndef START_H
#define START_H

#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class Start : public Statement
{
private:
	

	Connector* pOutConn;	
	

	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	Start(Point Lcorner);


	virtual void Draw(Output* pOut) const;

	Point GetLeftCorner() const;
	Point GetOutLet1() const;
	void SetOutConn1(Connector* C);
	virtual void Save(ofstream& OutFile);
	Connector* GetOutConn1();
};

#endif