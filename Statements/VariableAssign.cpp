#include "VariableAssign.h"
#include <sstream>
#include"../ApplicationManager.h"
using namespace std;

VariableAssign::VariableAssign(Point Lcorner, string LeftHS, string RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddVariableAssign) action
	//       before passing it to the constructor of VariableAssign
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void VariableAssign::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void VariableAssign::setRHS(string R)
{
	RHS = R;
	UpdateStatementText();
}


void VariableAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

Point VariableAssign::GetLeftCorner()
{
	return LeftCorner;
}

Point VariableAssign::GetInLet() const
{
	return Inlet;
}

Point VariableAssign::GetOutLet1() const
{
	return Outlet;
}

void VariableAssign::get_all(string& l, string& r) const
{
	l = this->LHS;
	r = this->RHS;
}

void VariableAssign::SetOutConn1(Connector* C)
{
	pOutConn = C;
}

void VariableAssign::Edit(ApplicationManager* pManager)
{
	string l, r;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Please Enter Left Hand Side");
	l = pIn->GetVariabel(pOut);

	pOut->PrintMessage("Please Enter Right Hand Side");
	r = pIn->GetVariabel(pOut);
	this->setRHS(r);
	this->setLHS(l);
	pOut->ClearStatusBar();
}


Connector* VariableAssign::GetOutConn1()
{
	return pOutConn;
}



//This function should be called when LHS or RHS changes
void VariableAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = " << RHS;
	Text = T.str();
}

void VariableAssign::Save(ofstream& OutFile)
{
	OutFile << "VAR_ASSIGN" << " " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << RHS << "\n";
}

void VariableAssign::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
	UpdateStatementText();
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

}



bool VariableAssign::isInside(Point P)
{
	if (P.x <= LeftCorner.x + UI.ASSGN_WDTH
		&& P.x >= LeftCorner.x
		&& P.y >= LeftCorner.y
		&& P.y <= LeftCorner.y + UI.ASSGN_HI)
	{
		return true;
	}
	return false;
}
Statement* VariableAssign::Simulate(ApplicationManager* pAppManager)
{
	variable* pVar1 = pAppManager->FindVar(LHS);
	variable* pVar2 = pAppManager->FindVar(RHS);
	pVar1->value = pVar2->value;
	return pOutConn->getDstStat();
}

Statement* VariableAssign::GenerateCode(ofstream& OutFile)
{
	OutFile << LHS << " = " << RHS << ";\n";
	return pOutConn->getDstStat();
}