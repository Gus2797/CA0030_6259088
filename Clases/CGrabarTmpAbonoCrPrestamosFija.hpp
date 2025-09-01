#ifndef CGRABARTMPABONOCRPRESTAMOSFIJA
#define CGRABARTMPABONOCRPRESTAMOSFIJA
#include "stdafx.h"
#include <RecordSet.HPP>
class CGrabarTmpAbonoCrPrestamosFija : public CRecordSet 
{
public:
    CGrabarTmpAbonoCrPrestamosFija(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpAbonoCrPrestamosFija();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[10];
    int nCTipo[10];
    long nLongitud[10];
    long nLongResp[10];
    void *pVar[10];
    
    long                cliente;
    short int           tienda;
    long                factura;
    long                interesadicional;
    long                saldoactual;
    long                importeultimomovimiento;
    SqlTimeStamp        fechaultimomovimiento;
    short int           caja;
    short int           sistema;
};
#endif CGRABARTMPABONOCRPRESTAMOSFIJA
