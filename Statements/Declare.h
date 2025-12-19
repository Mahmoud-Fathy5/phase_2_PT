#pragma once

#include "Statement.h"


class Declare : public Statement
{
private:
	string var;	
	Connector* pOutConn;	

	Point Inlet;	
	Point Outlet;	
	

	Point LeftCorner;	
	

	virtual void UpdateStatementText();

public:
	Declare(Point Lcorner, string var = "");

	void setVar(const string& var);

	virtual void Draw(Output* pOut) const;

	Point GetLeftCorner() const;
	Point GetInLet() const;
	Point GetOutLet1() const;
	

	void SetOutConn1(Connector* C);

	Connector* GetOutConn1();
	string get_var()const;
	void Edit(ApplicationManager* pManager) override;
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);
	bool isInside(Point);



	virtual Statement* Simulate(ApplicationManager* pManager);
	virtual Statement* GenerateCode(ofstream& OutFile);
	Declare() = default;

	Statement* Valid(ApplicationManager* pManager) override;
};
