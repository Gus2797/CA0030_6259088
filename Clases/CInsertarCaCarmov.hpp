#ifndef CINSERTARCACARMOV
#define CINSERTARCACARMOV
#include "stdafx.h"
#include <RecordSet.HPP>
class CInsertarCaCarmov : public CRecordSet 
{
public:
    CInsertarCaCarmov(C_ODBC *odbc_ext, const char *select=NULL);
    ~CInsertarCaCarmov();
    void activarCols();
    BOOL prepararInsert();
    BOOL prepararInsert(const char *tabla);
    
    C_ODBC *odbc;
    int odbcRet;
    int nCols;
    int flagInsertar;
    int nSqlTipo[12];
    int nCTipo[12];
    long nLongitud[12];
    long nLongResp[12];
    void *pVar[12];
    
    char                clave[3];
    char                tipomovimiento[3];
    short int           tienda;
    short int           ciudad;
    long                cliente;
    short int           caja;
    char                movtoseguro[3];
    long                folio;
    SqlTimeStamp        fecha;
    long                efectuo;
    SqlTimeStamp        fechanacimiento;
};
#endif CINSERTARCACARMOV
