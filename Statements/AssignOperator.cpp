#include "AssignOperator.h"
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

void AssignOperator::SetOutConn(Connector* C)
{
	pOutConn = C;
}
Point AssignOperator::GetInLet() const
{
	return Inlet;
}

Point AssignOperator::GetOutLet() const
{
	return Outlet;
}


//This function should be called when LHS or RHS changes
void AssignOperator::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T << LHS << " = "<<RHS_1<<" " << op << " " << RHS_2;
	Text = T.str();
}