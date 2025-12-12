#include "Statement.h"
int Statement::temp = 0;
Statement::Statement()	
{ 
	//TODO: set the ID with a unique value
	Text = "";
	Selected = false;	
	ID = temp;
	temp++;
}

void Statement::SetSelected(bool s)
{	Selected = s; }

bool Statement::IsSelected() const
{	return Selected; }

Point Statement::GetInLet() const
{
	return Point();
}

Point Statement::GetOutLet() const
{
	return Point();
}

int Statement::GetID() const
{
	return ID;
}

void Statement::Save(ofstream& OutFile)
{

}