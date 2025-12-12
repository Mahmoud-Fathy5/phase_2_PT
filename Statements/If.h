#pragma once


#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class If : public Statement
{
private:
	string LHS;
	string op;
	string RHS;
	Connector* pOutConn;	//Right Handside (Value)

	//Value Assignment Stat. has one Connector to next statement
	//Each statement type in flowchart has a predefined number of (output) connectors
	//For example, conditional statement always has 2 output connectors

	//Note: We don't need to keep track with input connectors
	//      Whenever we want to iterate on all statements of the flowchart
	//      we will begin with start statement then its output connector
	//      then the connector's destination statement and so on (follow the connectors)

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet1;	//A point a connection leaves this statement
	Point Outlet2;
	//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	If(Point Lcorner, string LeftHS, string RightHS = "", string oper = "");

	void setLHS(const string& L);
	void setRHS(string R);
	void setOp(string O);

	Point GetInlet() const;
	Point GetOutlet1() const;
	Point GetOutlet2()const;
	void SetOutConn(Connector* C);

	virtual void Draw(Output* pOut) const;
	Point GetLeftCorner();
};

