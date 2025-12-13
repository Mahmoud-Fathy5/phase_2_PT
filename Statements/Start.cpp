#include "Start.h"
#include <sstream>
using namespace std;

Start::Start(Point Lcorner)
{
	

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	

	Outlet.x = LeftCorner.x + UI.OVAL_WDTH / 2;
	Outlet.y = LeftCorner.y + UI.OVAL_HI;
}




void Start::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	//pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
	pOut->Drawstart(LeftCorner,UI.OVAL_WDTH,UI.OVAL_HI,Selected);

}

//Point Start::GetOutlet() const
//{
//	return Outlet;
//}

void Start::SetOutConn(Connector* C)
{
	pOutConn = C;
}


Point Start::GetLeftCorner() const
{
	return LeftCorner;
}

Point Start::GetOutLet()const
{ 
	return Outlet;
}



void Start::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	//ostringstream T;
	//T <<"Start";
	//Text = T.str();
}

void Start::Save(ofstream& OutFile)
{
	OutFile << "STRT" << " " << ID << " " << LeftCorner.x << " " << LeftCorner.y << "\n";
}

void Start::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y;
	pOutConn = NULL;	//No connectors yet



	Outlet.x = LeftCorner.x + UI.OVAL_WDTH / 2;
	Outlet.y = LeftCorner.y + UI.OVAL_HI;

}

