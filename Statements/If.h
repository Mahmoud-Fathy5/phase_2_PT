#pragma once


#include "Statement.h"


class If : public Statement
{
private:
	string LHS;
	string op;
	string RHS;
	Connector* pOutConn1;	
	Connector* pOutConn2;

	

	Point Inlet;	//A point where connections enters this statement 
	Point Outlet1;
	Point Outlet2;
	

	Point LeftCorner;	//left corenr of the statement block.
	
	bool visted;
	virtual void UpdateStatementText();

public:
	If(Point Lcorner, string LeftHS, string RightHS = "", string oper = "");

	void setLHS(const string& L);
	void setRHS(string R);
	void setOp(string O);

	void SetOutConn1(Connector* C);
	void SetOutConn2(Connector* C);

	void get_all(string &l,string &h,string &o)const;

	virtual void Draw(Output* pOut) const;
	void Edit(ApplicationManager* pManager) override;
	Point GetInLet() const;
	Point GetOutLet1() const;
	
	Point GetOutLet2()const;

	Connector* GetOutConn1();
	Connector* GetOutConn2();

	bool isInside(Point);
	bool GetVisted() const;


	Point GetLeftCorner();
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	virtual Statement* Simulate(ApplicationManager* pManager);
	virtual Statement* GenerateCode(ofstream& OutFile);
	If() = default;
	Statement* Valid(ApplicationManager* pManager) override;

	
};

