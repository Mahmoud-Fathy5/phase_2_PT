#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "GUI\UI_Info.h"
#include "GUI\output.h"
#include "Actions/Save.h"
class Statement;

class Connector	//a connector that connects two statements (Source & Destination)
{
private:
	Statement *SrcStat;	//The source statement of the connector
	Statement *DstStat;	//The destination statement of the connector
	Point start;	//Start point of the connector
	//Point Start1;
	//Point Start2;
	Point end;		//End point of the connector

	bool isSelected;
public:
	Connector(Statement* Src, Statement* Dst);

	void		setSrcStat(Statement *Src);
	Statement*	getSrcStat();	
	void		setDstStat(Statement *Dst);
	Statement*	getDstStat();

	void setStartPoint(Point P);

	//void setStart1Point(Point P);
	//void setStart2Point(Point P);


	//Point getStart1Point(Point P);
	//Point getStart2Point(Point P);



	Point getStartPoint();

	void setEndPoint(Point P);
	Point getEndPoint();


	bool IsSelected() const;

	void SetSelected(bool s);
	

	void Draw(Output* pOut) const;
	
	void Save(ofstream& OutFile);

};

#endif