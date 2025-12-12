#include "Save.h"

#include "..\ApplicationManager.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

Save::Save(ApplicationManager* pAppManager):Action(pAppManager)
{
}

void Save::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	string filename;
	filename = pIn->GetString(pOut);
	system("mkdir SavedCharts");
	OutFile.open("SavedCharts//" + filename + ".txt");


}

void Save::Execute()
{
	ReadActionParameters();
	pManager->saveStatements(OutFile);
	pManager->saveConn(OutFile);
	OutFile.close();

}
