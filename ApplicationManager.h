#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"

#include "Statements\Statement.h"
class Input;
class Output;

struct variable
{
	string name ;
	double value;
	bool assigned=false;

	bool isInitialize = false;

};


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxCount = 200 };	//Max no of statements/connectors in a single flowchart

private:
	int StatCount;		//Actual number of statements
	int ConnCount;		//Actual number of connectors
	Statement* StatList[MaxCount];	//List of all statements (Array of pointers)
	Connector* ConnList[MaxCount];	//List of all connectors (Array of pointers)

	Statement *pSelectedStat; //a pointer to the last selected statement
	                          //you can set and get this pointer
	Statement *pClipboard;    //a pointer to the last copied/cut statement
	bool Copy0_or_Cut1 = 0;
	bool Error = 0;
	                          //you can set and get this pointer
	Connector* pSelectedConn;

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;
	variable* Vars[MaxCount];
	int VarCount;
	bool isValid;

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// == Actions Related Functions ==
	ActionType GetUserAction() const; //Reads the input command from the user 
	                                  //and returns the corresponding action type
	void ExecuteAction(ActionType) ;  //Creates an action and executes it
	
	// == Statements/Connector Management Functions ==
	void AddStatement(Statement* pStat);    //Adds a new Statement to the Flowchart
	Statement *GetStatement(Point P) const;	//Searches for a statement where point P belongs
	                                        //TODO: Complete its implementation 
	                                        //      WITHOUT breaking class responsibilities

	void AddConnector(Connector* pConn);    //Adds a new Connector to the Flowchart
	Connector *GetConnector(Point P) const;	//search for a Connector where point P belongs


	void saveStatements(ofstream& OutFile);
	void saveConn(ofstream& OutFile);
	Statement* FindStatement(int id);
	// Note: you should use the following 4 functions 
	//       in order not to break class responsibilities (especially in copy, cut and paste)
	Statement *GetSelectedStatement() const;	 //Returns the selected Statement
	void SetSelectedStatement(Statement *pStat); //Set the Statement selected by the user
	Statement *GetClipboard() const;	         //Returns the Clipboard
	void SetClipboard(Statement *pStat);         //Set the Clipboard
	bool get_Copy0_Cut1()const;
	void set_Copy0_Cut1(bool b);


	bool get_error();
	void set_error(bool b);


	Connector* GetSelectedConn()const;
	void SetSelectedConn(Connector* pConn);

	void DeleteConn(Connector* pConn);
	void DeleteStat(Statement* pStat);

	// == Interface Management Functions ==
	Input *GetInput() const;        //Return pointer to the input
	Output *GetOutput() const;      //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window


	Statement* GetStart();
	
	void AddVar(variable*);
	variable* FindVar(string name);
	void printVars() const;
	void killVars();

	void SetIsValid(bool);
	bool GetIsValid();

	void Validate_Statements_Connection_and_reset();
};


#endif