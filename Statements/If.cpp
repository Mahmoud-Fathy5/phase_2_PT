#include "If.h"
#include <sstream>
#include"../ApplicationManager.h"
#include <string>
#include "../Actions/Validate.h"
using namespace std;

If::If(Point Lcorner, string LeftHS, string RightHS, string oper)
{
	// Note: The LeftHS and RightHS should be validated inside (AddIf) action
	//       before passing it to the constructor of If
	LHS = LeftHS;
	RHS = RightHS;
	op = oper;
	visted = false;
	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn1 = NULL;	//No connectors yet
	pOutConn2 = NULL;

	Inlet.x = LeftCorner.x + UI.COND_WDTH/2;
	Inlet.y = LeftCorner.y;

	Outlet1.x = LeftCorner.x+UI.COND_WDTH;
	Outlet1.y = LeftCorner.y + UI.COND_HI/2;

	Outlet2.x = LeftCorner.x;
	Outlet2.y = LeftCorner.y + UI.COND_HI / 2;

	//Outlet2.x= Inlet.x;
	//Outlet2.y= LeftCorner.y + UI.COND_HI;//Edit Co-ordinates
}



void If::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void If::setOp(string O)
{
	op = O;
	UpdateStatementText();
}

void If::setRHS(string R)
{
	RHS = R;
	UpdateStatementText();
}



void If::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawCondtional(LeftCorner, UI.COND_WDTH, UI.COND_HI, Text, Selected); //need to be considerd

}

Point If::GetLeftCorner()
{
	return LeftCorner;
}

void If::Edit(ApplicationManager* pManager)
{
	string l, o, r;
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Please Enter Left Hand Side");
	l = pIn->GetVariabelOrValue(pOut);

	pOut->PrintMessage("Please Enter Comparator ");
	o = pIn->GetCompOperator(pOut);


	//ValueOrVariable()
	pOut->PrintMessage("Please Enter Right Hand Side ");
	r = pIn->GetVariabelOrValue(pOut);
	this->setLHS(l);
	this->setOp(o);
	this->setRHS(r);
	pOut->ClearStatusBar();
}

Point If::GetInLet() const
{
	return Inlet;
}


Point If::GetOutLet1() const
{
	return Outlet1;
}







Point If::GetOutLet2() const
{
	return Outlet2;
}

void If::SetOutConn1(Connector* C)
{
	pOutConn1 = C;
}
void If::SetOutConn2(Connector* C)
{
	pOutConn2 = C;
}

void If::get_all(string& l, string& h, string& o) const
{
	l = this->LHS;
	h = this->RHS;
	o = this->op;
	
}


Connector* If::GetOutConn1()
{
	return pOutConn1;
}


Connector* If::GetOutConn2()
{
	return pOutConn2;
}

bool If::GetVisted() const
{
	return visted;
}






//This function should be called when LHS or RHS changes
void If::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T <<"If " << LHS << " " << op << " " << RHS;
	Text = T.str();
}

void If::Save(ofstream& OutFile)
{
	OutFile << "COND" << " " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " 
		<< LHS << " " << op << " " << RHS << "\n";
}

void If::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> op >> RHS;
	UpdateStatementText();
	pOutConn1 = NULL;	//No connectors yet
	pOutConn2 = NULL;
	Inlet.x = LeftCorner.x + UI.COND_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet1.x = LeftCorner.x + UI.COND_WDTH;
	Outlet1.y = LeftCorner.y + UI.COND_HI / 2;

	Outlet2.x = LeftCorner.x;
	Outlet2.y = LeftCorner.y + UI.COND_HI / 2;
	visted = false;

}


bool If::isInside(Point P)
{
	if(P.x >= GetLeftCorner().x
		&& P.x <= GetLeftCorner().x + UI.COND_WDTH
		&& P.y >= GetLeftCorner().y
		&& P.y <= GetLeftCorner().y + UI.COND_HI)
	{
		return true;
	}
	return false;
}
Statement* If::Simulate(ApplicationManager* pAppManager)
{
	variable* pVar1;
	variable* pVar2;
	bool status = false;
	if (IsVariable(LHS))
	{
		pVar1 = pAppManager->FindVar(LHS);
		if (IsVariable(RHS))
		{
			pVar2 = pAppManager->FindVar(RHS);
			if (op == "==") status = pVar1->value == pVar2->value;
			if (op == ">") status = pVar1->value > pVar2->value;
			if (op == "<") status = pVar1->value < pVar2->value;
			if (op == ">=") status = pVar1->value >= pVar2->value;
			if (op == "<=") status = pVar1->value <= pVar2->value;
			if (op == "!=") status = pVar1->value != pVar2->value;
		}
		else if (IsValue(RHS))
		{
			double d = stod(RHS);
			if (op == "==") status = pVar1->value == d;
			if (op == ">") status = pVar1->value > d;
			if (op == "<") status = pVar1->value < d;
			if (op == ">=") status = pVar1->value >= d;
			if (op == "<=") status = pVar1->value <= d;
			if (op == "!=") status = pVar1->value != d;
		}
	}
	else if (IsValue(LHS))
	{
		double d = stod(LHS);
		if (IsVariable(RHS))
		{
			pVar2 = pAppManager->FindVar(RHS);
			if (op == "==") status = d == pVar2->value;
			if (op == ">") status = d > pVar2->value;
			if (op == "<") status = d < pVar2->value;
			if (op == ">=") status = d >= pVar2->value;
			if (op == "<=") status = d <= pVar2->value;
			if (op == "!=") status = d != pVar2->value;
		}
		else if (IsValue(RHS))
		{
			double d1 = stod(RHS);
			if (op == "==") status = d == d1;
			if (op == ">") status = d > d1;
			if (op == "<") status = d < d1;
			if (op == ">=") status = d >= d1;
			if (op == "<=") status = d <= d1;
			if (op == "!=") status = d != d1;
		}
	}
	if (status)
		return pOutConn1->getDstStat();
	else
		return pOutConn2->getDstStat();
}

Statement* If::GenerateCode(ofstream& OutFile)
{
	if (visted == false)
	{
		OutFile << "while(" << LHS << op << RHS << "){\n";

		visted = true;
		return pOutConn1->getDstStat();
	}
	else
	{
		OutFile << "}\n";
		visted = false;
		return pOutConn2->getDstStat();
	}
}

Statement* If::Valid(ApplicationManager* pManager)
{
	set_is_visited(true);
	Output* pOut = pManager->GetOutput();
	if (!(pManager->FindVar(LHS)) && IsVariable(LHS)) {
		pOut->OutputMessages("Error: Variable "+ LHS + " Not declared");
		pManager->set_error(true);
	}
	if ((pManager->FindVar(LHS)) && IsVariable(LHS) && (pManager->FindVar(LHS))->assigned == false) {
		pOut->OutputMessages("Error: Variable " + LHS + " Not Intialized");
		pManager->set_error(true);
	}
	if (!(pManager->FindVar(RHS)) && IsVariable(RHS)) {
		pOut->OutputMessages("Error: Variable " + RHS + " Not declared");
		pManager->set_error(true);
	}
	if ((pManager->FindVar(RHS)) && IsVariable(RHS) && (pManager->FindVar(LHS))->assigned == false) {
		pOut->OutputMessages("Error: Variable " + RHS + " Not Intialized");
		pManager->set_error(true);
	}
	if (pOutConn1 && !( (pOutConn1->getDstStat())->get_is_visited() ) ) {

		Validate True_Con(pManager);
		True_Con.Execute_if(pOutConn1->getDstStat());
	}
	else if (!pOutConn1) {

		pOut->OutputMessages("Error: No Output True Connector from the if Statement");
		pManager->set_error(true);
		return NULL;
	}
	if (pOutConn2 && !((pOutConn2->getDstStat())->get_is_visited())) {
		return pOutConn2->getDstStat();
	}
	else if (!pOutConn2){

		pOut->OutputMessages("Error: No Output False Connector from the if Statement");
		pManager->set_error(true);
		return NULL;
	}
	return NULL;
}


