#include "If.h"
#include <sstream>

using namespace std;

If::If(Point Lcorner, string LeftHS, string RightHS, string oper)
{
	// Note: The LeftHS and RightHS should be validated inside (AddIf) action
	//       before passing it to the constructor of If
	LHS = LeftHS;
	RHS = RightHS;
	op = oper;

	UpdateStatementText();

	LeftCorner = Lcorner;

	pOutConn = NULL;	//No connectors yet

	Inlet.x = LeftCorner.x + UI.COND_WDTH / 2;
	Inlet.y = LeftCorner.y;

	Outlet1.x = Inlet.x;
	Outlet1.y = LeftCorner.y + UI.COND_HI;

	Outlet2.x= Inlet.x;
	Outlet2.y= LeftCorner.y + UI.COND_HI;//Edit Co-ordinates
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

Point If::GetInlet() const
{
	return Inlet;
}

Point If::GetOutlet1() const
{
	return Outlet1;
}

Point If::GetOutlet2() const
{
	return Outlet2;
}

void If::SetOutConn(Connector* C)
{
	pOutConn = C;
}



//This function should be called when LHS or RHS changes
void If::UpdateStatementText()
{
	//Build the statement text: Left handside then equals then right handside
	ostringstream T;
	T <<"IF " << LHS << " " << op << " " << RHS;
	Text = T.str();
}