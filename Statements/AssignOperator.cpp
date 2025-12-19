#include "AssignOperator.h"
#include"../ApplicationManager.h"
#include <sstream>
#include <string>

using namespace std;

AssignOperator::AssignOperator(Point Lcorner, string LeftHS, string RightHS_1 , string oper , string RightHS_2 )
{
	// Note: The LeftHS and RightHS should be validated inside (AddAssignOperator) action
	//       before passing it to the constructor of AssignOperator
	LHS = LeftHS;
	RHS_1 = RightHS_1;
	RHS_2 = RightHS_2;
	op = oper;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;
}

void AssignOperator::setLHS(const string& L)
{
	LHS = L;
	UpdateStatementText();
}

void AssignOperator::setOp(string O)
{
	op = O;
	UpdateStatementText();
}

void AssignOperator::get_all(string& LeftHS, string& RightHS_1, string& oper, string& RightHS_2) const
{
	LeftHS = this->LHS;
	RightHS_1 =this->RHS_1 ;
	oper = this->op;
	RightHS_2 = this->RHS_2;
}

void AssignOperator::setRHS_1(string R1)
{
	RHS_1 = R1;
	UpdateStatementText();
}

void AssignOperator::setRHS_2(string R2)
{
	RHS_2 = R2;
	UpdateStatementText();
}



void AssignOperator::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);

}

Point AssignOperator::GetLeftCorner()
{
	return LeftCorner;
}

void AssignOperator::Edit(ApplicationManager* pManager)
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	string l, op, r1,r2;
	pOut->PrintMessage("Please Enter Left Hand Side");
	l = pIn->GetVariabel(pOut);


	pOut->PrintMessage("Please Enter First Operand Right Hand Side ");
	r1 = pIn->GetVariabelOrValue(pOut);

	pOut->PrintMessage("Please Enter Operator ");
	op = pIn->GetArithOperator(pOut);

	pOut->PrintMessage("Please Enter Second Operand Right Hand Side ");
	r2 = pIn->GetVariabelOrValue(pOut);
	this->setLHS(l);
	this->setRHS_1(r1);
	this->setOp(op);
	this->setRHS_2(r2);
	pOut->ClearStatusBar();
}


Point AssignOperator::GetInLet() const
{
	return Inlet;
}

Point AssignOperator::GetOutLet1() const
{
	return Outlet;
}


Connector * AssignOperator:: GetOutConn1()
{
	return pOutConn;
}


void AssignOperator::SetOutConn1(Connector* C)
{
	pOutConn = C;
}



//This function should be called when LHS or RHS changes
void AssignOperator::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = "<<RHS_1<<" " << op << " " << RHS_2;
	Text = T.str();
}

void AssignOperator::Save(ofstream& OutFile)
{
	OutFile << "OP_ASSIGN" << " " << ID << " " << LeftCorner.x << " " << LeftCorner.y << " " 
		<< LHS << " " << RHS_1 << " " << op << " " << RHS_2 << "\n";
}

void AssignOperator::Load(ifstream& InFile)
{
	InFile >> ID >> LeftCorner.x >> LeftCorner.y >> LHS >> RHS_1 >> op >> RHS_2;
	UpdateStatementText();
	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.ASSGN_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet.x = Inlet.x;
	Outlet.y = LeftCorner.y + UI.ASSGN_HI;

}


bool AssignOperator::isInside(Point P)
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
Statement* AssignOperator::Simulate(ApplicationManager* pAppManager)
{
	variable* pVar1 = pAppManager->FindVar(LHS);
	variable* pVar2;
	variable* pVar3;
	if (IsVariable(RHS_1))
	{
		pVar2 = pAppManager->FindVar(RHS_1);
		if (IsVariable(RHS_2))
		{
			pVar3 = pAppManager->FindVar(RHS_2);
			if(op == "+") pVar1->value = pVar2->value + pVar3->value;
			if (op == "*") pVar1->value = pVar2->value * pVar3->value;
			if (op == "-") pVar1->value = pVar2->value - pVar3->value;
			if (op == "/") pVar1->value = pVar2->value / pVar3->value;

		}
		else
		{
			if(op == "+") pVar1->value = pVar2->value + stod(RHS_2);
			if (op == "*") pVar1->value = pVar2->value * stod(RHS_2);
			if (op == "-") pVar1->value = pVar2->value - stod(RHS_2);
			if (op == "/") pVar1->value = pVar2->value / stod(RHS_2);

		}
	}
	else if (IsVariable(RHS_2))
	{
		pVar2 = pAppManager->FindVar(RHS_2);
		if(op == "+") pVar1->value = stod(RHS_1) + pVar2->value;
		if (op == "*") pVar1->value = stod(RHS_1) * pVar2->value;
		if (op == "-") pVar1->value = stod(RHS_1) - pVar2->value;
		if (op == "/") pVar1->value = stod(RHS_1) / pVar2->value;

	}
	return pOutConn->getDstStat();
}

Statement* AssignOperator::GenerateCode(ofstream& OutFile)
{
	OutFile << LHS << " = " << RHS_1 << " " << op << " " << RHS_2 << ";\n";
	return pOutConn->getDstStat();
}

Statement* AssignOperator::Valid(ApplicationManager* pManager)
{
	set_is_visited(true);
	Output* pOut = pManager->GetOutput();
	if (!(pManager->FindVar(LHS)) && IsVariable(LHS)) {
		pOut->PrintMessage("Error: Variable " + LHS + " Not declared");
		pManager->set_error(true);
	}
	
	if (!(pManager->FindVar(RHS_1)) && IsVariable(RHS_1)) {
		pOut->PrintMessage("Error: Variable " + RHS_1 + " Not declared");
		pManager->set_error(true);
	}
	if ((pManager->FindVar(RHS_1)) && IsVariable(RHS_1) && (pManager->FindVar(RHS_1))->assigned == false) {
		pOut->PrintMessage("Error: Variable " + RHS_1 + " Not Intialized");
		pManager->set_error(true);
	}
	if (!(pManager->FindVar(RHS_2)) && IsVariable(RHS_2)) {
		pOut->PrintMessage("Error: Variable " + RHS_2 + " Not declared");
		pManager->set_error(true);
	}
	if ((pManager->FindVar(RHS_2)) && IsVariable(RHS_2) && (pManager->FindVar(RHS_2))->assigned == false) {
		pOut->PrintMessage("Error: Variable " + RHS_2 + " Not Intialized");
		pManager->set_error(true);
	}


	if ((pManager->FindVar(LHS))&&(pManager->FindVar(RHS_1)) && IsVariable(RHS_1) && (pManager->FindVar(RHS_1))->assigned == true && (pManager->FindVar(RHS_2)) && IsVariable(RHS_2) && (pManager->FindVar(RHS_2))->assigned == true) {
		(pManager->FindVar(LHS))->assigned = true;
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
