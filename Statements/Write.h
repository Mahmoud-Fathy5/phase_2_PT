#pragma once
#include "Statement.h"


class	Write : public Statement
{
private:
	string VarorStr;	

	Connector* pOutConn;	

	Point Inlet;	
	Point Outlet;	

	Point LeftCorner;	
	virtual void UpdateStatementText();

public:
	Write(Point Lcorner, string var = "");

	void set_ValuOrVar(const string& L);

	virtual void Draw(Output* pOut) const;

	Point GetLeftCorner();
	Point GetInLet() const;
	Point GetOutLet1() const;
	string get_ValuOrVar()const;

	void SetOutConn1(Connector* C);
	virtual Connector* GetOutConn1();
	void Edit(ApplicationManager* pManager) override;
	virtual void Save(ofstream& OutFile);
	virtual void Load(ifstream& InFile);

	bool isInside(Point);

	virtual Statement* Simulate(ApplicationManager* pAppManager);
	virtual Statement* GenerateCode(ofstream& OutFile);
	Write() = default;
	Statement* Valid(ApplicationManager* pManager) override;
};
