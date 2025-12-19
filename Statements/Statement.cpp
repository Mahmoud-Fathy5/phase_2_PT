#include "Statement.h"
#include "Start.h"
#include "../Actions/Run.h"
int Statement::temp = 0;
Statement::Statement()	
{ 
	//TODO: set the ID with a unique value
	Text = "";
	is_visited = false;
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



int Statement::GetID() const
{
	return ID;
}

Point Statement::GetOutLet1() const
{
	return Point();
}


Point Statement::GetOutLet2() const
{
	return Point();
}





void Statement:: SetOutConn2(Connector*)
{
	return;
}






Connector *Statement::GetOutConn2()
{
	return NULL;
}




void Statement::Save(ofstream& OutFile)
{

}



void Statement::set_is_visited(bool b)
{
	is_visited = b;
}

bool Statement::get_is_visited() const
{
	return is_visited;
}

Statement::~Statement()
{
}
