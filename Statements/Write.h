#pragma once
#include "Statement.h"

//Value Assignment statement class
//The value assignment statement assigns a value to a variable
class	Write : public Statement
{
private:
	string VarorStr;	//Left Handside of the assignment (name of a variable)
	//Right Handside (Value)

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
};
