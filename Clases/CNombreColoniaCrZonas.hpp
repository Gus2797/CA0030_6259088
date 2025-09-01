#ifndef CNOMBRECOLONIACRZONAS
#define CNOMBRECOLONIACRZONAS
#include "stdafx.h"
#include <RecordSet.HPP>
class CNombreColoniaCrZonas : public CRecordSet 
{
public:
    CNombreColoniaCrZonas(C_ODBC *odbc_ext, const char *select=NULL);
    ~CNombreColoniaCrZonas();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[2];
    int nCTipo[2];
    long nLongitud[2];
    long nLongResp[2];
    void *pVar[2];
    
    char                nombrezona[32];
};
#endif CNOMBRECOLONIACRZONAS
