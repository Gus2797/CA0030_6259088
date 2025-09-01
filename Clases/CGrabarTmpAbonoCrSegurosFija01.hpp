#ifndef CGRABARTMPABONOCRSEGUROSFIJA01
#define CGRABARTMPABONOCRSEGUROSFIJA01
#include "stdafx.h"
#include <RecordSet.HPP>
class CGrabarTmpAbonoCrSegurosFija01 : public CRecordSet 
{
public:
    CGrabarTmpAbonoCrSegurosFija01(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpAbonoCrSegurosFija01();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[16];
    int nCTipo[16];
    long nLongitud[16];
    long nLongResp[16];
    void *pVar[16];
    
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
    char				nombreadicional[17];
    char				apellidopaternoadic[17];
    char				apellidomaternoadic[17];
    SqlTimeStamp        fecnacadic;
    short int           parentescoadic;
	short int           consecutivoseguro;	
};
#endif CGRABARTMPABONOCRSEGUROSFIJA01
