#include "AssignOperator.h"
#include"../ApplicationManager.h"
#include <sstream>

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


	//ValueOrVariable()
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

void AssignOperator::SetOutConn(Connector* C)
{
	pOutConn = C;
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