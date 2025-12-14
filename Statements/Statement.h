#ifndef STATEMENT_H
#define STATEMENT_H

#include "..\defs.h"
#include "..\Connector.h"
//class Output;
#include "..\GUI\Output.h"
#include "../Actions/Save.h"
#include "../Actions/Load.h"
#include <sstream>
//Base class for all Statements
class Statement
{
	static int temp;
protected:
	int ID;			//Each Statement has an ID --> must be unique
	string Text;	//Statement text (e.g.  "X = 5" OR "salary > 3000" and so on)
	bool Selected;	//true if the statement is selected on the folwchart

	virtual void UpdateStatementText() = 0;	//is called when any part of the stat. is edited	

	/// Add more parameters if needed.

public:
	Statement();
	void SetSelected(bool s);
	bool IsSelected() const;
	int GetID() const;

	virtual Point  GetInLet() const ;
	//virtual Point  GetOutLet() const;
	virtual Point  GetOutLet1() const=0;
	virtual Point  GetOutLet2() const;

	virtual void Draw(Output* pOut) const  = 0 ;	//Draw the statement
	virtual void SetOutConn1(Connector*) = 0;
	virtual void SetOutConn2(Connector*);
	virtual Connector *GetOutConn1()=0;
	virtual Connector *GetOutConn2();

	virtual bool isInside(Point) = 0;
	

	///TODO:The following functions should be supported by the Statement class
	///		It should then be overridden by each derived Statement
	///		Decide the parameters that you should pass to each function and its return type

	virtual void Save(ofstream& OutFile) = 0; //Save the Statement parameters to a file
	virtual void Load(ifstream &InFile) = 0;	//Load the Statement parameters from a file

	virtual void Edit(ApplicationManager* pManager) = 0;		//Edit the Statement parameter

	virtual Statement* Simulate(ApplicationManager* pManager) = 0;	//Execute the statement in the simulation mode

	virtual Statement* GenerateCode(ofstream &OutFile) = 0;	//write the statement code to a file


	///TODO: Add more functions if needed
	virtual ~Statement();

};

#endif