#ifndef VARIABLE_ASSIGN_H
#define VARIABLE_ASSIGN_H

#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class VariableAssign : public Statement
{
private:
	string LHS;	//Left Handside of the assignment (name of a variable)
	string RHS;	//Right Handside (Variable)

	Connector* pOutConn;	//Value Assignment Stat. has one Connector to next statement

	

	Point Inlet;	//A point where connections enters this statement 
	//It's used as the (End) point of the (Input) connectors
	Point Outlet;	//A point a connection leaves this statement
	//It's used as the (Start) point of the (Output) connector

	Point LeftCorner;	//left corenr of the statement block.

	virtual void UpdateStatementText();

public:
	VariableAssign(Point Lcorner, string LeftHS = "", string RightHS = "");

	void setLHS(const string& L);
	void setRHS( string R); 

	virtual void Draw(Output* pOut) const;
	Point GetLeftCorner();
	Point GetInLet() const;
	Point GetOutLet1() const;
	void SetOutConn1(Connector* C);

	Connector* GetOutConn1();
	
	void get_all(string &l,string &r)const;
	
	void Edit(ApplicationManager* pManager) override;
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	bool isInside(Point);
	virtual Statement* Simulate(ApplicationManager* pManager);
	virtual Statement* GenerateCode(ofstream& OutFile);
	VariableAssign() = default;
	Statement* Valid(ApplicationManager* pManager) override;
};

#endif