#include "Declare.h"
#include <sstream>

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

void Declare::SetOutConn1(Connector* C)
{
	pOutConn = C;
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
	T << var;
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