#ifndef ASSIGN_OPERATOR_H
#define ASSIGN_OPERATOR_H

#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class AssignOperator : public Statement
{
private:
	string LHS;
	string op;
	string RHS_1;
	string RHS_2;
	Connector* pOutConn;	//Value Assignment Stat. has one Connector to next statement
	//Each statement type in flowchart has a predefined number of (output) connectors
	//For example, conditional statement always has 2 output connectors

	//Note: We don't need to keep track with input connectors
	//      Whenever we want to iterate on all statements of the flowchart
	//      we will begin with start statement then its output connector
	//      then the connector's destination statement and so on (follow the connectors)

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	AssignOperator(Point Lcorner, string LeftHS,string RightHS_1="", string oper="", string RightHS_2="");

	void setLHS(const string& L);
	void setRHS_1(string R1);
	void setRHS_2(string R2); //const by refrence
	void setOp(string O);
	void get_all(string& LeftHS, string& RightHS_1, string& oper, string& RightHS_2) const;

	Point GetInLet() const;
	Point GetOutLet1() const;
	void SetOutConn1(Connector* C);

	virtual void Draw(Output* pOut) const;
	Point GetLeftCorner();
	void Edit(ApplicationManager* pManager) override;
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);

	Connector *GetOutConn1();


	AssignOperator() = default;
};

#endif