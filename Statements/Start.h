#ifndef START_H
#define START_H

#include "Statement.h"
#include <sstream>


class Start : public Statement
{
private:
	

	Connector* pOutConn;	
	

	Point Outlet;	

	Point LeftCorner;	

	virtual void UpdateStatementText();

public:
	static bool exsit;

	Start(Point Lcorner);


	virtual void Draw(Output* pOut) const;

	Point GetLeftCorner() const;
	Point GetOutLet1() const;
	void SetOutConn1(Connector* C);
	virtual void Save(ofstream& OutFile);
	void Edit(ApplicationManager* pManager) override;
	~Start();
	Connector* GetOutConn1();
	virtual void Load(ifstream& InFile);

	bool isInside(Point);

	virtual Statement* Simulate(ApplicationManager* pAppManager);
	virtual Statement* GenerateCode(ofstream& OutFile);
	Start() = default;
	Statement* Valid(ApplicationManager* pManager) override;
};

#endif