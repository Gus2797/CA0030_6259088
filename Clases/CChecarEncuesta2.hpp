#ifndef CCHECARENCUESTA2
#define CCHECARENCUESTA2
#include "stdafx.h"
#include <RecordSet.HPP>
class CChecarEncuesta2 : public CRecordSet 
{
public:
    CChecarEncuesta2(C_ODBC *odbc_ext, const char *select=NULL);
    ~CChecarEncuesta2();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[7];
    int nCTipo[7];
    long nLongitud[7];
    long nLongResp[7];
    void *pVar[7];
    
    SqlTimeStamp        fecha;
    long                total30dias;
    long                totaledoscta;
    short int           status;
    long                totalencuestar;
    long                keyx;
};
#endif CCHECARENCUESTA2
