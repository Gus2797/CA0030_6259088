#ifndef CGRABARTMPCRPRESTAMOS
#define CGRABARTMPCRPRESTAMOS
#include "stdafx.h"
#include <RecordSet.HPP>
class CGrabarTmpCrPrestamos : public CRecordSet 
{
public:
    CGrabarTmpCrPrestamos(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpCrPrestamos();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[8];
    int nCTipo[8];
    long nLongitud[8];
    long nLongResp[8];
    void *pVar[8];
    
    long                cliente;
    short int           tienda;
    long                factura;
    long                interesadicional;
    long                saldoactual;
    long                importeultimomovimiento;
    SqlTimeStamp        fechaultimomovimiento;
};
#endif CGRABARTMPCRPRESTAMOS
