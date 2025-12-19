#include "ValueAssign.h"
#include <sstream>
#include"../ApplicationManager.h"
using namespace std;

ValueAssign::ValueAssign(Point Lcorner, string LeftHS, double RightHS)
{
	// Note: The LeftHS and RightHS should be validated inside (AddValueAssign) action
	//       before passing it to the constructor of ValueAssign
	LHS = LeftHS;
	RHS = RightHS;

	UpdateStatementText();

	LeftCorner = Lcorner;
	
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH /2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;	
}

void ValueAssign::setLHS(const string &L)
{
	LHS = L;
	UpdateStatementText();
}

void ValueAssign::setRHS(double R)
{
	RHS = R;
	UpdateStatementText();
}


void ValueAssign::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
	
}

Point ValueAssign::GetLeftCorner()
{
	return LeftCorner;
}

Point ValueAssign::GetInLet() const
{
	return Inlet;
}

Point ValueAssign::GetOutLet1() const
{
	return Outlet;
}

void ValueAssign::get_all(string& l, double& r) const
{
	l = this->LHS;
	r = this->RHS;
}

void ValueAssign::SetOutConn1(Connector* C)
{
	pOutConn = C;
}

void ValueAssign::Edit(ApplicationManager* pManager)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	string l;
	double r;
	pOut->PrintMessage("Please Enter Left Hand Side");
	l = pIn->GetVariabel(pOut);

	pOut->PrintMessage("Please Enter Right Hand Side");
	r = pIn->GetValue(pOut);
	this->setLHS(l);
	this->setRHS(r);
	pOut->ClearStatusBar();
}


Connector* ValueAssign ::GetOutConn1()
{
	return pOutConn;
}



//This function should be called when LHS or RHS changes
void ValueAssign::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T<<LHS<<" = "<<RHS;	
	Text = T.str();	 
}

void ValueAssign::Save(ofstream& OutFile)
{
	OutFile << "VAL_ASSIGN" << " " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << LHS << " " << RHS << "\n";
}

void ValueAssign::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS;
	UpdateStatementText();
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

}


bool ValueAssign::isInside(Point P)
{
	if (P.x <= GetLeftCorner().x + UI.ASSGN_WDTH
		&& P.x >= GetLeftCorner().x - UI.ASSGN_WDTH
		&& P.y >= GetLeftCorner().y
		&& P.y <= GetLeftCorner().y + UI.ASSGN_HI)
	{
		return true;
	}
	return false;
}
Statement* ValueAssign::Simulate(ApplicationManager* pAppManager)
{
	variable* pVar = pAppManager->FindVar(LHS);
	pVar->value = RHS;
	pVar->assigned = true;
	return pOutConn->getDstStat();
}

Statement* ValueAssign::GenerateCode(ofstream& OutFile)
{
	OutFile << LHS << " = " << RHS << ";\n";
	return pOutConn->getDstStat();
}

Statement* ValueAssign::Valid(ApplicationManager* pManager)
{
	set_is_visited(true);
	Output* pOut = pManager->GetOutput();
	if (!(pManager->FindVar(LHS))) {
		pOut->PrintMessage("Error: Variable "+LHS+" Not declared");
		pManager->set_error(true);
	}
	else {
		( pManager->FindVar(LHS) )->assigned = true;
	}



	if (pOutConn && !((pOutConn->getDstStat())->get_is_visited())) {
		return pOutConn->getDstStat();
	}
	else if (!pOutConn) {
		
		pOut->OutputMessages("Error: No Output Connector from the Assign Statement");
		pManager->set_error(true);
		return NULL;
	}
	return NULL;
}

