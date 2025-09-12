#ifndef CLOGBONIFICACIONDIARIA
#define CLOGBONIFICACIONDIARIA

#include "stdafx.h"
#include <RecordSet.HPP>

class CLogBonificacionDiaria : public CRecordSet 
{
public:
    CLogBonificacionDiaria(C_ODBC *odbc_ext, const char *select=NULL);
    ~CLogBonificacionDiaria();
    void activarCols();
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];
    
    long                estado;
    char                mensaje[20001];
};

#endif // CLOGBONIFICACIONDIARIA