#ifndef CGRABARTMPCRCMUEBLES
#define CGRABARTMPCRCMUEBLES
#include "stdafx.h"
#include <RecordSet.HPP>
class CGrabarTmpCrCmuebles : public CRecordSet 
{
public:
    CGrabarTmpCrCmuebles(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpCrCmuebles();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[6];
    int nCTipo[6];
    long nLongitud[6];
    long nLongResp[6];
    void *pVar[6];
    
    long                cliente;
    long                factura;
    long                saldo;
    long                interesadicional;
    SqlTimeStamp        fechaultimomovimiento;
};
#endif CGRABARTMPCRCMUEBLES
