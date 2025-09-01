// Consulta original solicitada:...
//  SELECT poliza as poliza2, nombreadicional FROM fun_consultaradicional('9027773672')

#ifndef CADIIONALC
#define CADIIONALC
#include "stdafx.h"
#include <RecordSet.hpp>
class CAdiional : public CRecordSet
{
public:
    CAdiional(C_ODBC *odbc_ext, const char *select = NULL);
    ~CAdiional();
    void activarCols();

    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int nSqlTipo[3];
    int nCTipo[3];
    long nLongitud[3];
    long nLongResp[3];
    void *pVar[3];

    _int64              poliza2;
    char                nombreadicional[20001];
};
#endif CADIIONALC
