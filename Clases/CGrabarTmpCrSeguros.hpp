#ifndef CGRABARTMPCRSEGUROS
#define CGRABARTMPCRSEGUROS
#include "stdafx.h"
#include <RecordSet.HPP>
class CGrabarTmpCrSeguros : public CRecordSet 
{
public:
    CGrabarTmpCrSeguros(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpCrSeguros();
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
    long                folio;
    SqlTimeStamp        fechavencimiento;
    short int           cvesinbeneficiarios;
    short int           cantidadseguros;
    short int           claveconyugal;
    char                claveseguro[3];
};
#endif CGRABARTMPCRSEGUROS
