#ifndef CGRABARTMPABONOCRSEGUROSFIJA
#define CGRABARTMPABONOCRSEGUROSFIJA
#include "stdafx.h"
#include <RecordSet.HPP>
class CGrabarTmpAbonoCrSegurosFija : public CRecordSet 
{
public:
    CGrabarTmpAbonoCrSegurosFija(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpAbonoCrSegurosFija();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[11];
    int nCTipo[11];
    long nLongitud[11];
    long nLongResp[11];
    void *pVar[11];
    
    long                cliente;
    long                folio;
    SqlTimeStamp        fechavencimiento;
    short int           cvesinbeneficiarios;
    short int           cantidadseguros;
    short int           claveconyugal;
    char                claveseguro[3];
    short int           caja;
    short int           sistema;
    short int           tienda;
};
#endif CGRABARTMPABONOCRSEGUROSFIJA
