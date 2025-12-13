#include "End.h"
#include <sstream>
#include"../ApplicationManager.h"
using namespace std;

bool End::exist = false;

End::End(Point Lcorner)
{

	exist = true;
	UpdateStatementText();
	
	LeftCorner = Lcorner;

	//pInConn = NULL;	//No connectors yet



	Inlet.x = LeftCorner.x + UI.OVAL_WDTH / 2;
	Inlet.y = LeftCorner.y ;
}




void End::Draw(Output* pOut) const
{
	//Call Output::DrawAssign function to draw assignment statement 	
	//pOut->DrawAssign(LeftCorner, UI.ASSGN_WDTH, UI.ASSGN_HI, Text, Selected);
	pOut->DrawEnd(LeftCorner, UI.OVAL_WDTH, UI.OVAL_HI, Selected);

}

Point End::GetLeftCorner() const
{
	return LeftCorner;
}

Point End::GetInLet() const
{
	return Inlet;
}



void End::UpdateStatementText()
{

}

void End::Save(ofstream& OutFile)
{
	OutFile << "END" << " " << ID << " " << LeftCorner.x << " " << LeftCorner.y << "\n";
}

void End::Edit(ApplicationManager* pManager)
{
}

End ::~End() {
	exist = false;
}