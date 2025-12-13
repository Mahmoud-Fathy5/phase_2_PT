#include "Paste.h"
#include "AddStart.h"
#include "AddEnd.h"
#include "AddAssignOperator.h"
#include "AddAssignVariable.h"
#include "AddDeclare.h"
#include "AddRead.h"
#include "AddIf.h"
#include "AddValueAssign.h" 
#include "AddWrite.h" 

#include "Delete.h"
Paste::Paste(ApplicationManager* pAppManager) :Action(pAppManager)
{
}

void Paste::ReadActionParameters()
{
	pStat_copy = pManager->GetClipboard();
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();


	pIn->GetPointClicked(Position);
	while (!(Position.x <UI.DrawingAreaWidth && Position.y >UI.ToolBarHeight && Position.y < (UI.height-UI.StatusBarHeight))) {
		(pManager->GetOutput())->PrintMessage("You Should Draw in the Drawing Area Only, Click anywhere in the Drawing Area");
		pIn->GetPointClicked(Position);
	}
	while ((pManager->GetStatement(Position))) {
		(pManager->GetOutput())->PrintMessage("You cannot Put Statement Above The other , click anywhere else");
		pIn->GetPointClicked(Position);
	}
	pOut->ClearStatusBar();
}

void Paste::Execute()
{
	ReadActionParameters();
	bool isStart = false, isEnd = false;
	if (pStat_copy != NULL ) {

		if (dynamic_cast<Start*>(pStat_copy)) {
			if (Start::exsit && ((pManager->get_Copy0_Cut1()) == false)) return;
			Start* ptr = new Start(Position);
			pManager->AddStatement(ptr);
			isStart = true;
		}
		else if (dynamic_cast<End*>(pStat_copy)) {
			if (End::exist && ((pManager->get_Copy0_Cut1()) == false)) return;
			End* ptr = new End(Position);
			pManager->AddStatement(ptr);
			isEnd = true;
		}
		else if (dynamic_cast<AssignOperator*>(pStat_copy)) {
			string l, op, r1, r2;
			((AssignOperator*)pStat_copy)->get_all(l, r1, op, r2);
			AssignOperator* ptr = new AssignOperator(Position,l,r1,op,r2);
			pManager->AddStatement(ptr);
		}
		else if (dynamic_cast<ValueAssign*>(pStat_copy)) {
			string l;
			double r;
			((ValueAssign*)pStat_copy)->get_all(l, r);
			ValueAssign* ptr = new ValueAssign(Position,l,r);
			pManager->AddStatement(ptr);

		}
		else if (dynamic_cast<VariableAssign*>(pStat_copy)) {
			string l, r;
			((VariableAssign*)pStat_copy)->get_all(l,r);
			VariableAssign* ptr = new VariableAssign(Position,l,r);
			pManager->AddStatement(ptr);

		}

		else if (dynamic_cast<Declare*>(pStat_copy)) {
			string var= ((Declare*)pStat_copy)->get_var();
			Declare* ptr = new Declare(Position,var);
			pManager->AddStatement(ptr);

		}
		else if (dynamic_cast<Read*>(pStat_copy)) {
			string var = ((Read*)pStat_copy)->get_var();
			Read* ptr = new Read(Position,var);
			pManager->AddStatement(ptr);
		}
		else if (dynamic_cast<If*>(pStat_copy)) {
			string l, o, r;
			((If*)pStat_copy)->get_all(l, r,o);
			If* ptr = new If(Position,l,r,o);
			pManager->AddStatement(ptr);
		}
		else if (dynamic_cast<Write*>(pStat_copy)) {
			string s;
			s= ((Write*)pStat_copy)->get_ValuOrVar();
			Write* ptr = new Write(Position,s);
			pManager->AddStatement(ptr);
		}

		
	}
	else {
		Output* pOut = pManager->GetOutput();
		pOut->PrintMessage("There Is No Selected Copied Statement");
		return;
	}
	if ((pManager->get_Copy0_Cut1()) == 1) {
		Delete d(pManager);
		d.Execute();
		if (isStart)
			Start::exsit = true;
		if (isEnd)
			End::exist = true;

		pManager->SetClipboard(NULL);
	}

}
