#include "Validate.h"

#include "..\Statements\If.h"

#include "..\Statements\End.h"
#include"..\Statements\Statement.h"
#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

#include <sstream>
using namespace std;

//constructor: set the ApplicationManager pointer inside this action
Validate::Validate(ApplicationManager* pAppManager) :Action(pAppManager)
{
	
}

void Validate::ReadActionParameters()
{

}

void Validate::Execute()
{
	Output* pOut = pManager->GetOutput();
	if (!(Start::exsit)) {
		pOut->OutputMessages("InValid There is no Start");
		pManager->set_error(true);

	}
	if (!(End::exist)) {
		pOut->OutputMessages("InValid There is no End");
		pManager->set_error(true);
	}
	Statement* pStat = pManager->GetStart();
	
	while ( (pStat != NULL) )
	{

		pStat = pStat->Valid(pManager);
	}
		if ((pManager->get_error()) == false) {
			pOut->OutputMessages("Valid");
		}	
		 pManager->killVars();
		 pManager->set_error(false);
		 pManager->Validate_Statements_Connection_and_reset();
}
void Validate::Execute_if(Statement* ptr)
{
	Statement* pStat =ptr ;
	Output* pOut = pManager->GetOutput();
	while ((pStat != NULL))
	{
		pStat = pStat->Valid(pManager);
	}

}
