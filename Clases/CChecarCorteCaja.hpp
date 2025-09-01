#ifndef CCHECARCORTECAJA
#define CCHECARCORTECAJA
#include "stdafx.h"
#include <RecordSet.HPP>
class CChecarCorteCaja : public CRecordSet 
{
public:
    CChecarCorteCaja(C_ODBC *odbc_ext, const char *select=NULL);
    ~CChecarCorteCaja();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[4];
    int nCTipo[4];
    long nLongitud[4];
    long nLongResp[4];
    void *pVar[4];
    
    long                billetes2000;
    long                numempcajero;
    long                numempgte;
};
#endif CCHECARCORTECAJA
