#ifndef END_H
#define END_H

#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class End : public Statement
{
private:


	Connector* pOutConn;

	Point Inlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.


public:
	End(Point Lcorner);


	virtual void Draw(Output* pOut) const;
	virtual void UpdateStatementText();
	Point GetLeftCorner() const;
	Point GetInLet() const;
	virtual void Save(ofstream& OutFile);
	Connector* GetOutConn1();
	Point GetOutLet1() const;
	void SetOutConn1(Connector* C);
	virtual void Load(ifstream& InFile);

	End() = default;
};

#endif
