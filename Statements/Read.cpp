#include "Read.h"
#include <sstream>
#include"../ApplicationManager.h"
using namespace std;

Read::Read(Point Lcorner, string v)
{
	// Note: The LeftHS and RightHS should be validated inside (AddRead) action
	//       before passing it to the constructor of Read
	 var= v;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI; //need tobe condiderd
}

void Read::setVar(const string& L)
{

	var = L;
	UpdateStatementText();
}


void Read::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawRead(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected); //need to be considerd

}

Point Read::GetLeftCorner()
{
	return LeftCorner;
}

Point Read::GetInLet() const
{
	return Inlet;
}

Point Read::GetOutLet1() const
{
	return Outlet;
}

string Read::get_var() const
{
	return this->var;
}

void Read::SetOutConn(Connector* C)
void Read::SetOutConn1(Connector* C)
{
	pOutConn = C;
}

void Read::Edit(ApplicationManager* pManager)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	string s;
	pOut->PrintMessage("Please Enter var");
	s = pIn->GetVariabel(pOut);
	this->setVar(s);
	pOut->ClearStatusBar();
}


Connector* Read::GetOutConn1()
{
	return pOutConn;
}


//This function should be called when LHS or RHS changes
void Read::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << var;
	Text = T.str();
}

void Read::Save(ofstream& OutFile)
{
	OutFile << "READ" << " " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << var << "\n";
}
void Read::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> var;
	UpdateStatementText();

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI; //need tobe condiderd

}