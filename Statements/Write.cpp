#include "Write.h"
#include <sstream>
#include"../ApplicationManager.h"
using namespace std;

Write::Write(Point Lcorner, string v)
{
	// Note: The LeftHS and RightHS should be validated inside (AddWrite) action
	//       before passing it to the constructor of Write
	this->VarorStr = v;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI; //need tobe condiderd
}

void Write::set_ValuOrVar(const string& L)
{
	VarorStr = L;
	UpdateStatementText();
}


void Write::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawWrite(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected); //need to be considerd

}

Point Write::GetLeftCorner()
{
	return LeftCorner;
}

Point Write::GetInLet() const
{
	return Inlet;
}

Point Write::GetOutLet1() const
{
	return Outlet;
}

string Write::get_ValuOrVar() const
{
	return this->VarorStr;
}

void Write::SetOutConn1(Connector* C)
{
	pOutConn = C;
}

void Write::Edit(ApplicationManager* pManager)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	string s;
	pOut->PrintMessage("Please Enter Variable name or String");
	s = pIn->GetStringlOrVariable(pOut);
	this->set_ValuOrVar(s);
}




//This function should be called when LHS or RHS changes
void Write::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << VarorStr;
	Text = T.str();
}

Connector* Write::GetOutConn1()
{
	return pOutConn;
}

void Write::Save(ofstream& OutFile)
{
	OutFile << "WRITE" << " " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " << VarorStr << "\n";
}

void Write::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> VarorStr;
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI; //need tobe condiderd
	UpdateStatementText();
}

Statement* Write::Simulate(ApplicationManager* pAppManager)
{
	ostringstream T;
	Input* pIn = pAppManager->GetInput();
	Output* pOut = pAppManager->GetOutput();
	if (IsVariable(VarorStr))
	{
		variable* pVar = pAppManager->FindVar(VarorStr);
		T << VarorStr << " = " << pVar->value;
	}
	else
	{
		T << VarorStr;
	}
	pOut->OutputMessages(T.str());
	return pOutConn->getDstStat();
}


bool Write::isInside(Point P)
{
	if (P.x >= GetLeftCorner().x
		&& P.x <= GetLeftCorner().x + UI.ASSGN_WDTH
		&& P.y >= GetLeftCorner().y
		&& P.y <= GetLeftCorner().y + UI.ASSGN_HI)
	{
		return true;
	}
	return false;
}
Statement* Write::GenerateCode(ofstream& OutFile)
{
	OutFile << "cout << " << VarorStr << ";\n";
	return pOutConn->getDstStat();
}

Statement* Write::Valid(ApplicationManager* pManager)
{
	set_is_visited(true);
	Output* pOut = pManager->GetOutput();
	if (!(pManager->FindVar(VarorStr)) && IsVariable(VarorStr)) {
		pOut->OutputMessages("Error: Variable" + VarorStr + "Not declared");
		pManager->set_error(true);
	}
	if (pOutConn && !((pOutConn->getDstStat())->get_is_visited())) {
		return pOutConn->getDstStat();
	}
	else if (!(pOutConn)) {

		pOut->OutputMessages("Error: No Output Connector from the Write Statement");
		pManager->set_error(true);
		return NULL;
	}
	return NULL;
}
