#include "Declare.h"
#include <sstream>
#include"../ApplicationManager.h"

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
	var = pIn->GetVariabel(pOut);
	string s;
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


bool Declare:: isInside(Point P)
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