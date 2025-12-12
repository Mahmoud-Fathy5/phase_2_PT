#ifndef ADD_CONNECTOR_H  
#define ADD_CONNECTOR_H  

#include "Action.h"  
#include "../Connector.h"  
#include "../Statements/Statement.h"  

class AddConn: public Action
{
private:  
    Statement* SrcStat; // The source statement of the connector  
    Statement* DstStat; // The destination statement of the connector  
    Point start;        // Start point of the connector  
    Point end;          // End point of the connector  

public:  
    AddConn(ApplicationManager* pAppManager);  
    virtual void ReadActionParameters();  
    virtual void Execute();  
};  

#endif