#include "Declare.h"
#include <sstream>
#include"../ApplicationManager.h"
#include "../Actions/Run.h"

using namespace std;

Declare::Declare(Point Lcorner, string v)
{
	// Note: The LeftHS and RightHS should be validated inside (AddDeclare) action
	//       before passing it to the constructor of Declare
	var = v;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void Declare::setVar(const string& L)
{
	var = L;
	UpdateStatementText();
}


void Declare::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

Point Declare::GetLeftCorner() const
{
	return LeftCorner;
}

Point Declare::GetInLet() const
{
	return Inlet;
}

Point Declare::GetOutLet1() const
{
	return Outlet;
}

string Declare::get_var() const
{
	return this->var;
}

void Declare::SetOutConn1(Connector* C)
{
	pOutConn = C;
}

void Declare::Edit(ApplicationManager* pManager)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Please Enter varaiable");
	string s;
	s = pIn->GetVariabel(pOut);
	
	this->setVar(s);
	pOut->ClearStatusBar();
}




Connector* Declare::GetOutConn1()
{
	return pOutConn;
}



//This function should be called when LHS or RHS changes
void Declare::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T <<"Double "<< var;
	Text = T.str();
}


void Declare::Save(ofstream& OutFile)
{
	OutFile << "DECLARE" << " " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << var << "\n";
}

void Declare::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> var;
	UpdateStatementText();
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

}


bool Declare::isInside(Point P)
{
	if (P.x < GetLeftCorner().x + UI.ASSGN_WDTH
		&& P.x > GetLeftCorner().x
		&& P.y > GetLeftCorner().y
		&& P.y < GetLeftCorner().y + UI.ASSGN_HI)
	{


		return true;
	}
	return false;
}



Statement* Declare::Simulate(ApplicationManager* pManager)
{
	variable* pVar = new variable;
	pVar->name = var;
	pManager->AddVar(pVar);
	return pOutConn->getDstStat();
}


Statement* Declare::GenerateCode(ofstream& OutFile)
{
	OutFile << "double " << var << ";\n";
	return pOutConn->getDstStat();
}

Statement* Declare::Valid(ApplicationManager* pManager)
{
	set_is_visited(true);
	variable* pVar = new variable;
	Output* pOut = pManager->GetOutput();
	pVar->name = get_var();
	if (pManager->FindVar(pVar->name)) {
		pOut->OutputMessages("Error: Variable "+pVar->name +" already declared");
		pManager->set_error(true);
	}
	else {
		pManager->AddVar(pVar);
	}
	
	if ( pOutConn && !((pOutConn->getDstStat())->get_is_visited()) ) {
		return pOutConn->getDstStat();
	}
	else if (!pOutConn){
		
		pOut->OutputMessages("Error: No Output Connector from the Decalre Statement");
		pManager->set_error(true);
		return NULL;
	}
	return NULL;
}
