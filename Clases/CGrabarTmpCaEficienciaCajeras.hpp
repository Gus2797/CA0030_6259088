#ifndef CGRABARTMPCAEFICIENCIACAJERAS
#define CGRABARTMPCAEFICIENCIACAJERAS
#include "stdafx.h"
#include <RecordSet.HPP>
class CGrabarTmpCaEficienciaCajeras : public CRecordSet 
{
public:
    CGrabarTmpCaEficienciaCajeras(C_ODBC *odbc_ext, const char *select=NULL);
    ~CGrabarTmpCaEficienciaCajeras();
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
    
    short int           tienda;
    SqlTimeStamp        fechaeficienciacajera;
    short int           caja;
    long                recibo;
    long                cliente;
    long                empleado;
    long                cuentasconsaldo;
    long                cuentasconvencido;
    long                cuentasconvencidosinconvenio;
    long                cuentasconconvenio;
};
#endif CGRABARTMPCAEFICIENCIACAJERAS
