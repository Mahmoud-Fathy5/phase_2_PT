#include "Start.h"
#include <sstream>
using namespace std;
#include"../ApplicationManager.h"



bool Start::exsit = false;

Start::Start(Point Lcorner)
{

	exsit = true;
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
	pOut->Drawstart(LeftCorner, UI.OVAL_WDTH, UI.OVAL_HI, Selected);

}

//Point Start::GetOutlet() const
//{
//	return Outlet;
//}

void Start::SetOutConn1(Connector* C)
{
	pOutConn = C;
}


Point Start::GetLeftCorner() const
{
	return LeftCorner;
}

Point Start::GetOutLet1()const
{
	return Outlet;
}


Connector* Start::GetOutConn1()
{
	return pOutConn;
}



void Start::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << "Start";
	Text = T.str();
}

void Start::Save(ofstream& OutFile)
{
	OutFile << "START" << " " << ID << " " << LeftCorner.x << " " << LeftCorner.y << "\n";
}

void Start::Edit(ApplicationManager* pManager)
{
}

Start::~Start()
{
	exsit = false;
}

void Start::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y;
	pOutConn = NULL;	//No connectors yet



	Outlet.x = LeftCorner.x + UI.OVAL_WDTH / 2;
	Outlet.y = LeftCorner.y + UI.OVAL_HI;

}


bool Start::isInside(Point P)
{
	if(P.x >= GetLeftCorner().x
		&& P.x <= GetLeftCorner().x + UI.OVAL_WDTH
		&& P.y >= GetLeftCorner().y
		&& P.y <= GetLeftCorner().y + UI.OVAL_HI)
		{
		return true;
		}
	return false;
Statement* Start::Simulate(ApplicationManager* pAppManager)
{
	return pOutConn->getDstStat();
}

Statement* Start::GenerateCode(ofstream& OutFile)
{
	return pOutConn->getDstStat();
}
