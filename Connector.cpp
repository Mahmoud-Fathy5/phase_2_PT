#include "Connector.h"
#include"Statements/Statement.h"


Connector::Connector(Statement* Src, Statement* Dst)	
//When a connector is created, it must have a source statement and a destination statement
//There are NO FREE connectors in the flowchart
{
	
	SrcStat = Src;
	DstStat = Dst;
	start = Src->GetOutLet();
	end = Dst->GetInLet();
	isSelected = false;
}

void Connector::setSrcStat(Statement *Src)
{	SrcStat = Src;	}

Statement* Connector::getSrcStat()
{	return SrcStat;	}

void Connector::setDstStat(Statement *Dst)
{	DstStat = Dst;	}

Statement* Connector::getDstStat()
{	return DstStat;	}


void Connector::setStartPoint(Point P)
{	start = P;	}

Point Connector::getStartPoint()
{	return start;	}

void Connector::setEndPoint(Point P)
{	end = P;	}

Point Connector::getEndPoint()
{	return end;	}

bool Connector::IsSelected() const
{
	return isSelected;
}

void Connector::SetSelected(bool s)
{
	isSelected = s;
}


void Connector::Draw(Output* pOut) const
{
	

	///TODO: Call Output to draw a connector from SrcStat to DstStat on the output window
	pOut->DrawConnector(start, end,isSelected);
}

void Connector::Save(ofstream& OutFile)
{
	OutFile << SrcStat->GetID() << " " << DstStat->GetID() << "\n";
}

