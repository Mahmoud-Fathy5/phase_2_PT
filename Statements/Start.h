#ifndef START_H
#define START_H

#include "Statement.h"
#include <sstream>

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

	//Start() = default;

	bool isInside(Point);

	virtual Statement* Simulate(ApplicationManager* pAppManager);
	virtual Statement* GenerateCode(ofstream& OutFile);
	Start() = default;
};

#endif