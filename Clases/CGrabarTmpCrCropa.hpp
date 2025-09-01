#ifndef CGRABARTMPCRCROPA
#define CGRABARTMPCRCROPA
#include "stdafx.h"
#include <RecordSet.HPP>
class CGrabarTmpCrCropa : public CRecordSet 
{
public:
    CGrabarTmpCrCropa(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpCrCropa();
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
    
    long                cliente;
    long                saldo;
    long                minimoapagar;
    long                interesadicional;
    SqlTimeStamp        fechaultimomovimiento;
    short int           flagactualizacion;
};
#endif CGRABARTMPCRCROPA
